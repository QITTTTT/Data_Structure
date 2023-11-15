#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

//TODO:二叉树的顺序存储
//----------------二叉树的顺序存储表示------------------
typedef int TELemType;
#define MAX_TREE_SIZE 100
typedef TELemType SqBiTree[MAX_TREE_SIZE];
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
//TODO:队列及基本操作
typedef BiTNode* QElemType;
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
//初始化
Status InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)    exit(OVERFLOW);
    Q.front->next=nullptr;
    return OK;
}
//销毁队列
Status Destroy(LinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }
    return OK;
}
//插入元素
Status EnQueue(LinkQueue &Q,QElemType e){
    QNode*p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)  return OVERFLOW;
    p->data=e;p->next=nullptr;
    Q.rear->next=p;Q.rear=p;
    return OK;
}
//删除队头元素
Status DeQueue(LinkQueue &Q,QElemType &e){
    if(Q.front==Q.rear) return false;
    QueuePtr p=Q.front->next;
    Q.front->next=p->next;
    if(p==Q.rear)   Q.rear=Q.front;
    e=p->data;
    free(p);
    return OK;
}
//判空
bool QueueEmpty(LinkQueue Q){
    if(Q.front==Q.rear) return true;
    return false;
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
//先序递归
void PreOrderTraverse(BiTree T){
    if(T){
        visit(T);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
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
//TODO:线索二叉树
//-----------------二叉树的二叉线索存储表示----------------
typedef char TElemType;
enum PointerTag{Link,Thread};
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;
//中序线索化
void InThreading(BiThrTree &p,BiThrTree &pre){
    if(p){
        InThreading(p->lchild,pre);
        if(!p->lchild) {p->lchild=pre;p->LTag=Thread;}
        if(!pre->rchild) {pre->rchild=p;pre->RTag=Thread;}
        pre=p;
        InThreading(p->rchild,pre);
    }
}
Status InOrderThreading(BiThrTree &Thrt,BiThrTree T){
    Thrt=(BiThrNode*)malloc(sizeof(BiThrNode));
    if(!Thrt)   exit(OVERFLOW);
    Thrt->LTag=Link;Thrt->RTag=Thread;Thrt->rchild=Thrt;
    if(!T)  Thrt->lchild=Thrt;
    else{
        Thrt->lchild=T;
        BiThrNode*pre=Thrt,*p=T;
        InThreading(p,pre);
        pre->RTag=Thread;pre->rchild=Thrt;
        Thrt->rchild=p;
    }
    return OK;
}
//TODO:赫夫曼树
//--------------赫夫曼树和赫夫曼编码的存储表示-----------------
typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
//--------------------------赫夫曼编码---------------------------
void Select(HuffmanTree T,int n,int &m1,int &m2){
    if(n==1)    m1=m2=n;
    else if(n==2)  {m1=1;m2=2;}
    else{
        int k=1;
        while(T[k].parent!=0)   k++;
        m1=k;k++;
        while(T[k].parent!=0)   k++;
        m2=k;
        for(int i=k+1;i<=n;i++){
            if(T[i].parent==0){if(T[i].weight<T[m1].weight){
                if(T[i].weight<T[m2].weight){
                    if(T[m1].weight<T[m2].weight) m2=i;
                    else m1=1;
                }else{
                    m1=i;
                }
            }else if(T[i].weight<T[m2].weight){
                m2=i;
            }}
        }
    }
}
void StrCopy(char*p,char*q){
    int i=0;
    while(q[i]!='\0'){
        p[i]=q[i];
        i++;
    }
    p[i]='\0';
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,unsigned int *w,int n){
    //w存放n个字符的权值,n是字符个数
    if(n<1) return;
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元弃用，用来标记没有parent的结点
    if(!HT) exit(OVERFLOW);
    for(int i=1;i<=n;i++)   HT[i]={w[i],0,0,0};
    for(int i=n+1;i<=m;i++) HT[i]={0,0,0,0};
    for(int i=n;i<m;i++){
        int m1,m2;
        Select(HT,i,m1,m2);
        HT[i+1].weight=HT[m1].weight+HT[m2].weight;
        HT[i+1].lchild=m1;HT[i+1].rchild=m2;
        HT[m1].parent=i+1;HT[m2].parent=i+1;
    }
    //---------------------求哈夫曼编码---------------------
    /*
    HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    if(!HC) exit(OVERFLOW);
    char *cd = (char*)malloc(n*sizeof(char));
    if(!cd) exit(OVERFLOW);cd[n-1]='\0';
    for(int i=1;i<=n;i++){
        int start=n-1;
        for(int j=i,k=HT[j].parent;k>0;j=k,k=HT[j].parent){
            if(HT[k].lchild==j) cd[--start]='0';
            else if(HT[k].rchild==j)    cd[--start]='1';
        }
        HC[i]=(char*)malloc(n*sizeof(char));
        if(!HC[i])  exit(OVERFLOW);
        StrCopy(HC[i],&cd[start]);
    }
    free(cd);
    */
    //---------------------------------------------------------

    //-----------------------哈夫曼编码的无栈非递归算法----------------------

    HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    if(!HC) exit(OVERFLOW);
    char *cd = (char*)malloc(n*sizeof(char));
    if(!cd) exit(OVERFLOW);
    for(int i=1;i<=m;i++)   HT[i].weight=0;
    int p=m,start=0;
    while(p){
        if(HT[p].weight==0){
            HT[p].weight=1;
            if(HT[p].lchild!=0){
                p=HT[p].lchild;cd[start++]='0';
            }else{
                cd[start]='\0';
                HC[p]=(char*)malloc(n*sizeof(char));
                if(!HC[p])  exit(OVERFLOW);
                StrCopy(HC[p],cd);
                p=HT[p].parent;start--;
            }
        }else if(HT[p].weight==1){
            HT[p].weight=2;
            p=HT[p].rchild;cd[start++]='1';
        }else{
            p=HT[p].parent;start--;
        }
    }
    //---------------------------------------------------------------------
}
//TODO:6.33
bool Judge_u_v(int L[],int R[],int n,int u,int v){
    if(v==0)    return false;
    else if(u==v)   return true;
    else    return Judge_u_v(L,R,n,u,L[v])||Judge_u_v(L,R,n,u,R[v]);
}
//TODO:6.34
bool Judge_u_v_plus(int L[],int R[],int n,int u,int v,int *T){
    T=(int*)calloc(n+1,sizeof(int));
    if(!T)  exit(OVERFLOW);
    for(int i=1;i<=n;i++){
        T[L[i]]=i;T[R[i]]=i;
    }
    while(u!=0){
        if(u==v)    return true;
        else    u=T[u];
    }
    return false;
}
//TODO:6.35
int Decimal_valve(SqBiTree T,int i){
    return i+1;
}
//TODO:6.37
//继续练习一遍先序的非递归算法
void algorithm_6_37(BiTree T){
    if(!T)  return;
    SqStack S;InitStack(S);BiTNode*p=T;
    while(p||!StackEmpty(S)){
        if(!p){
            Push(S,p);visit(p);p=p->lchild;
        }
        else{
            Pop(S,p);p=p->rchild;
        }
    }
}
//TODO:6.39
typedef struct PlusBiTNode{
    TElemType data;
    struct PlusBiTNode *lchild,*rchild,*parent;
    int mark;
}PBiTNode,*PBiTree;
void PostOrderTraverse(PBiTree T){
    if(!T)  return;
    PBiTNode *p=T;
    while(p){
        if(p->mark==0){
            p->mark=1;
            if(p->lchild)   p=p->lchild;
        }else if(p->mark==1){
            p->mark=2;
            if(p->rchild)   p=p->rchild;
        }else if(p->mark==2){
            printf("%c",p->data);p=p->parent;
        }
    }
}
//TODO:6.42
int Leaf_amount(BiTree T){
    if(T){
        BiTNode*p=T;
        if(!p->lchild&&!p->rchild)  return 1;
        return Leaf_amount(p->lchild)+Leaf_amount(p->rchild);
    }
    return 0;
}
//TODO:6.43
void Switch(BiTree T){
    if(T){
        BiTNode*p=T->rchild;
        T->rchild=T->lchild;
        T->lchild=p;
        Switch(T->rchild);
        Switch(T->lchild);
    }
}
//TODO:6.45
void Delete_Node(BiTree &T){
    if(T){
        Delete_Node(T->lchild);
        Delete_Node(T->rchild);
        free(T);T=nullptr;
    }
}
void Delete_x(BiTree &T,char x){
    if(T){
        if(T->data==x){
            Delete_Node(T);
        }else{
            Delete_x(T->lchild,x);
            Delete_x(T->rchild,x);
        }
    }
}
//TODO:6.47
void LevelTraverse(BiTree T){
    if(T){
        LinkQueue Q;InitQueue(Q);EnQueue(Q,T);BiTNode*p;
        while(!QueueEmpty(Q)){
            DeQueue(Q,p);visit(p);
            if(p->lchild)   EnQueue(Q,p->lchild);
            if(p->rchild)   EnQueue(Q,p->rchild);
        }
    }    
}
//TODO:6.48
//用结点值代替结点指针
int Closest_Common_Ancestor(BiTree T,char p,char q){
    if(!T)  return 0;
    int left=Closest_Common_Ancestor(T->lchild,p,q);int right=Closest_Common_Ancestor(T->rchild,p,q);
    if(T->data==p||T->data==q){
        if(left+right==1) {visit(T);return 0;}
        else    return 1;
    }
    if(left+right==2){visit(T);return 0;}
    return left+right;
}
//TODO:6.49
/*
    算法思想：采用层次遍历算法，将所有节点加入队列(包括空结点)。遇到空结点时应判断其后是否还有非空结点。
*/
bool IsCompleteBTree(BiTree T){
    if(!T) return true;
    int tag=0;
    LinkQueue Q;InitQueue(Q);EnQueue(Q,T);BiTNode*p;
    while(!QueueEmpty(Q)){
        DeQueue(Q,p);
        if(p==nullptr&&tag==0)  tag=1;
        else if(p==nullptr&&tag==1)  return false;
        else{
               EnQueue(Q,p->lchild);
               EnQueue(Q,p->rchild);
        }
    }
    return true;
}
//TODO:6.50
Status CreateBiTree(BiTree &T,char A[][3],int i){
    if(A[i][0]=='^'&&A[i][1]=='^')  T=nullptr;
    else{
        T=(BiTNode*)malloc(sizeof(BiTNode));
        if(!T)  exit(OVERFLOW);
        T->data=A[i][1];T->lchild=T->rchild=nullptr;
        int j=1;
        while(A[j][1]!='^'){
            if(A[j][0]==T->data){
                if(A[j][2]=='L')    CreateBiTree(T->lchild,A,j);
                else CreateBiTree(T->rchild,A,j);
            }
            j++;
        }
    }
    return OK;
}
//TODO:6.51
void Print_Expression(BiTree T,int tag){
    if(T){
        int Ttag=0;
        if((T->data=='-'||T->data=='+')&&tag)  printf("(");
        if(T->data=='*'||T->data=='/')  Ttag=1;
        Print_Expression(T->lchild,Ttag);
        visit(T);
        Print_Expression(T->rchild,Ttag);
        if((T->data=='-'||T->data=='+')&&tag)  printf(")");
    }
}
//TODO:6.54

int main(){
    char p[]="ABC  DE G  F   ";
    char q[]="-+a  *b  -c  d  /e  f  ";
    BiTree T;int i=0;
    CreateBiTree(T,q,i);
    Print_Expression(T,0);
    return 0;
}