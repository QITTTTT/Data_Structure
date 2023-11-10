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
先序，中序思想:
tip1.先左再右，当执行到最后一步时就不用记录根节点，即访问右子树应该把根节点退栈(递归以进行到最后一步)。
tip2.整个过程只有a.刚进入while1时执行while2;b.以及右子树存在时执行while2。因此在右子树不存在时，需要向前找到右子树存在的结点
后序思想:
tip1.关键是判断栈中的结点执行到哪一步了，有两种方法
    1)因为我们依旧是先左后右，且冲突是由于判断右节点是否已经访问完了造成的，
    所以我们可以在visit时记录当前结点，这样返回上一层时就可以避免冲突。
    2)因为步数仅有两种，所以可以为每个节点设置tag{0,1}来标记。
栈的方法：本质上我们可以根据手算遍历序列的方法，用两个栈来模拟手算，得到序列。
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
//先序遍历(完善1)
/*
    根据tip2，我们只需要将根节点和右子树非空统一起来，
    tip3：设置辅助指针p始终指向右子树：p为空时出栈，p不空时执行根结点相同的操作(理解为它是新的根节点)
*/
Status PreOrderTraverse_me_2(BiTree T){
    SqStack S;InitStack(S);visit(T);Push(S,T);
    BiTNode*p=nullptr;
    while(!StackEmpty(S)){
        GetTop(S,p);
        if(!p)  Pop(S,p);
        else{
            while(p->lchild){p=p->lchild;visit(p);Push(S,p);}
        }
        if(!StackEmpty(S)){
            Pop(S,p);visit(p->rchild);Push(S,p->rchild);
        }
    }
    return OK;
}
//先序遍历(完善2)
/*
    对完善1进行简化，在已经把根结点和右子树统一的情况下，如果栈顶元素指向左子树时，p一定为空，即在左下寻找时多入一个空指针。
    可以转化为算法6.2;实质区别是：在递归上空指针也会进入递归，只是判空后立刻返回，完善1省略l进入递归这个操作。
*/
Status PreOrderTraverse_6_2(BiTree T){
    SqStack S;InitStack(S);visit(T);Push(S,T);
    BiTNode*p=nullptr;
    while(!StackEmpty(S)){
        GetTop(S,p);
        while(p){p=p->lchild;visit(p);Push(S,p);}
        Pop(S,p);
        if(!StackEmpty(S)){
            Pop(S,p);visit(p->rchild);Push(S,p->rchild);
        }
    }
    return OK;
}
//先序遍历(完善3)
Status PreOrderTraverse_6_3(BiTree T){
    SqStack S;InitStack(S);BiTNode*p=T;
    while(p||!StackEmpty(S)){
        if(p){
            visit(p);Push(S,p);p=p->lchild;
        }else{
            Pop(S,p);p=p->rchild;
        }
    }
    return OK;
}
//中序遍历
Status InOrderTraverse_6_3(BiTree T){
    SqStack S;InitStack(S);BiTNode *p=T;
    while(p||!StackEmpty(S)){
        if(p){
            Push(S,p);p=p->lchild;
        }else{
            Pop(S,p);visit(p);p=p->rchild;
        }
    }
    return OK;
}
//后序遍历
Status PostOrderTraverse(BiTree T){
    SqStack S;InitStack(S);BiTNode *p=T,*r=nullptr;
    while(p||!StackEmpty(S)){
        if(p){
            Push(S,p);p=p->lchild;
        }else{
            GetTop(S,p);
            if(p->rchild&&p->rchild!=r){
                p=p->rchild;
            }else{
                Pop(S,p);
                visit(p);
                r=p;
                p=nullptr;
            }
        }

    }
    return OK;
}
int main(){
    BiTree T;
    char ch[]="ABC  DE G  F   ";int i=0;
    CreateBiTree(T,ch,i);
    printf("建立完成");
    PostOrderTraverse(T);
    return 0;
}