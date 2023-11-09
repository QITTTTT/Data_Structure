#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

//TODO:二叉树的链式存储
typedef char ElemType;
typedef struct BiTNode{
    ElemType data;
    struct BiTNode*lchild,*rchild;
}BiTNode,*BiTree; 
//TODO：二叉树的建立(先序序列建立)
Status CreateBiTree(BiTree &T,char ch[],int &i){
    while(ch[i])
    {
        if(ch[i]==' ') {T=nullptr;i++;printf(" ");}
        else{
            T=(BiTree)malloc(sizeof(BiTNode));
            if(!T)  exit(OVERFLOW); T->data=ch[i];printf("%c",ch[i]);i++;
            CreateBiTree(T->lchild,ch,i);
            CreateBiTree(T->rchild,ch,i);
        }
       return OK; 

    }
    return OK;
}
//TODO: 遍历的非递归算法
//-----------------------------------相关栈的定义及操作--------------------------------------
//------------------------------------------------------------------------------------------
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量
typedef BiTNode* SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int  stacksize;
}SqStack;

// 初始化栈
Status InitStack(SqStack &s) {
    s.base = new SElemType[STACK_INIT_SIZE];
    if (!s.base) {
        exit(EXIT_FAILURE);
    }
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

// 入栈操作
Status Push(SqStack &s, SElemType e) {
    if (s.top - s.base >= s.stacksize) {
        // 栈满，追加存储空间
        SElemType *new_base = new SElemType[s.stacksize + STACKINCREMENT];
        for (int i = 0; i < s.stacksize; i++) {
            new_base[i] = s.base[i];
        }
        delete[] s.base;
        s.base = new_base;
        s.stacksize += STACKINCREMENT;
        s.top = s.base + s.stacksize;
    }
    *s.top = e;
    ++s.top;
    return OK;
}

// 出栈操作
Status Pop(SqStack &s, SElemType &e) {
    if (s.top == s.base) {
        return ERROR;
    }
    --s.top;
    e = *s.top;
    return OK;
}

// 判空操作
Status StackEmpty(SqStack &s) {
    if(s.top==s.base)
    return OK;
    else return FALSE;
}

// 读取栈顶元素
Status GetTop(SqStack s, SElemType &e){
    if(s.top==s.base)   return ERROR;
    e=*(s.top-1);
    return OK;
}
//清空
void ClearStack(SqStack &s) {
    while (!StackEmpty(s)) {
        SElemType e; // 假设 SElemType 是栈中元素的类型
        Pop(s, e);   // 使用 Pop 操作弹出栈顶元素，可以根据您的实际定义调用
    }
}
//销毁
void DestroyStack(SqStack &s) {
    if (s.base) {
        // 如果栈的底部指针（base）不为空，表示栈存在
        // 释放栈内元素所占用的内存
        free(s.base);
        s.base = NULL; // 将栈底部指针置为 NULL，表示栈已被销毁
        s.top = NULL;
        s.stacksize = 0;
    }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//****************************************三种遍历算法*******************************************
/*
1.先左再右，当执行到最后一步时就不用记录根节点，即访问右子树应该把根节点退栈(递归以进行到最后一步)。
2.整个过程只有a.刚进入while1时执行while2;b.以及右子树存在时执行while2。因此在右子树不存在时，需要向前找到右子树存在的结点
*/
//访问函数
void visit(BiTNode* T){
    if(T!=nullptr)
    printf("%c",T->data);
}
//先序遍历(自写)
Status PreOrderTraverse_me(BiTree T){
    if(!T)  return ERROR;
    SqStack S;InitStack(S);BiTNode*p;
    visit(T);Push(S,T);
    while(!StackEmpty(S)){
        GetTop(S,p);
        while(p->lchild){
            visit(p->lchild);Push(S,p->lchild);GetTop(S,p);
        }//while 2
        Pop(S,p);
        while(!StackEmpty(S)&&!p->rchild){
            Pop(S,p);
        }
        if(p->rchild) {visit(p->rchild);Push(S,p->rchild);}
    }//while 1
    DestroyStack(S);
    return OK;
}

int main(){
    BiTree T;
    char ch[]="ABC  DE G  F   ";int i=0;
    CreateBiTree(T,ch,i);
    printf("建立完成");
    PreOrderTraverse(T);
    return 0;
}