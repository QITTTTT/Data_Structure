#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
//TODO:page 143/03

// TODO:定义二叉树
typedef struct BiTNode{
    int value;
    struct BiTNode *lchild,*rchild;
}BiTNode,* BiTree;
// TODO:实现栈的操作
typedef struct{
    BiTNode* node[MaxSize];
    int top;
}SqStack;

void InitSqStack(SqStack &S){
    S.top=-1;
}

bool Pop(SqStack &S,BiTNode* &s){
    if(S.top<0)
        return false;
    s=S.node[S.top--];
    return true;
}

bool Push(SqStack &S,BiTNode* s){
    if(S.top>=MaxSize)
        return false;
    S.node[++S.top]=s;
    return true;
}
bool GetTop(SqStack S,BiTNode* &x){
    if(S.top==-1)
        return false;
    x=S.node[S.top];
    return true;
}
bool Isempty(SqStack S){
    if(S.top==-1)
        return true;
    else
        return false;
}
void visit(BiTNode* T){
    printf("%d",T->value);
}

//函数

bool PostOrder(BiTree T){
    if(T=nullptr)
        return false;
    SqStack S;
    InitSqStack(S);
    BiTNode* p = T,*r;
    while(p!=nullptr||S.top>-1)
    {
        if(p!=nullptr)
        {
            Push(S,p);
            p=p->rchild;
            
        }else{
            GetTop(S,p);
            if(p->rchild!=nullptr&&p->rchild!=r)
                p=p->rchild;
            else{
                Pop(S,p);
                visit(p);
                r=p;
                p=nullptr;
            }
        }
    }return true;
}

//TODO:page 143/04

//队列的基本操作
typedef struct LinkNode{
    BiTNode *data;
    struct LinkNode *next;
}LinkNode;
typedef struct {
    LinkNode *front,*rear;
}LinkQueue;
void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next=NULL;
}
bool IsEmpty(LinkQueue Q){
    if(Q.front==Q.rear)
    return true;
    else
    return false;
}

void EnQueue(LinkQueue &Q,BiTNode* x){
    LinkNode*s=(LinkNode*)malloc(sizeof(LinkNode));
    s->data=x;
    s->next=nullptr;
    Q.rear->next=s;
    Q.rear=s;
}

bool DeQueue(LinkQueue &Q,BiTNode* x){
    if(Q.front==Q.rear)
        return false;
    LinkNode *p=Q.front->next;
    x=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return true;
}
//end
void LevelOrder(BiTree T)
{
    LinkQueue Q;
    InitQueue(Q);
    SqStack S;
    InitSqStack(S);
    EnQueue(Q,T);
    BiTNode*p;
    while(!IsEmpty(Q))
    {
        DeQueue(Q,p);
        Push(S,p);
        if(p->lchild!=nullptr)
            EnQueue(Q,p->lchild);
        if(p->rchild!=nullptr)
            EnQueue(Q,p->rchild);
    }
    while(S.top>-1)
    {
        Pop(S,p);
        visit(p);
    }
}

//TODO:page 143/05
int BiTdepth(BiTree T){
    if(T==nullptr)
    {
        return 0;
    }
    else{
        int last=0,level=0;
        BiTNode* node[MaxSize];
        int front=-1,rear=-1;
        BiTNode*p=T;
        node[++rear]=p;
        while(front<rear)
        {
            p=node[++front];
            if(p->lchild)
                node[++rear]=p->lchild;
            if(p->rchild)
                node[++rear]=p->rchild;
            if(front==last)
                {  
                    level++;
                    last=rear;
                }

        }
      return level;  
    }
}
//TODO:page 143/06
BiTree build(int A[],int B[],int al,int ar,int bl,int br,int n){
    //al=bl=br=0;ar=n-1;
    if(n==0) return nullptr;
    BiTree T=(BiTree)malloc(sizeof(BiTNode));
    T->value=A[al];
    while(T->value!=B[br])
        {
            br++;
        }
    T->lchild=build(A,B,al+1,ar-n+1+br,bl,br-1,br-bl);
    T->rchild=build(A,B,br+1,n-1,br+1,n-1,n-1-br);
    return T;
}
//TODO:page 143/07
bool IsComplete(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTNode*p=T;
    EnQueue(Q,T);
    if(!p){
        return true;
    }
    while(!IsEmpty(Q))
    {
        DeQueue(Q,p);
        if(p!=nullptr)
        {EnQueue(Q,p->lchild);
        EnQueue(Q,p->rchild);}
        else{
            while(!IsEmpty(Q)){
            DeQueue(Q,p);
            if(p)
            return false;
            }
        }
    }
    return true;
}
//TODO:page 143/08
int DsonNodes(BiTree T){
    if(T->lchild==nullptr&&T->rchild==nullptr)
        return 0;
    if(T->lchild!=nullptr&&T->rchild!=nullptr)
        return 1+DsonNodes(T->lchild)+DsonNodes(T->rchild);
    else 
        return DsonNodes(T->lchild)+DsonNodes(T->rchild);
    
}
//TODO:page 144/9
void Exchange(BiTree T){
    if(T){Exchange(T->lchild);
    Exchange(T->rchild);
    BiTNode*p=T->lchild;
    T->lchild=T->rchild;
    T->rchild=p;}
}
//TODO:page 144/10
int k;
int find_k(BiTree T){
    if(T!=nullptr){
        if(k==1){
            return T->value;
        }
        if(k>1)
        {k--;
        return find_k(T->lchild);
        return find_k(T->rchild);}
    }
    return 0;
}

//TODO:page 144/11

void Delete(BiTree &T)/*删除结点*/
{
    if(T){
        Delete(T->lchild);
        Delete(T->rchild);
        BiTNode*temp=T;
        T=nullptr;
        free(temp);
    }
}
void Search_x0(BiTree T,int x)/*查找x值的结点并删除左右子树*/
{
    if(T)
    {
        if(T->value==x)
            {
                Delete(T->lchild);
                Delete(T->rchild);
            }
        else
        {Search_x0(T->lchild,x);
        Search_x0(T->rchild,x);}
    }
}
//TODO:page 144/012
void Search_x1(BiTree T,int x)/*查找x值并打印祖先*/
{
    SqStack S;
    InitSqStack(S);
    BiTNode*p=T;
    BiTNode*r=nullptr;
    while(p||!Isempty(S))
        if(p)
            {
                Push(S,p);
                p=p->lchild;
            }
        else
            {
                GetTop(S,p);
                if(p->rchild&&r!=p->rchild)
                    {
                        p=p->rchild;
                    }
                else
                    {
                        if(p->value==x)
                            {
                                Pop(S,p);
                                while(!Isempty(S))
                                    {
                                        printf("祖先元素的值为");
                                        Pop(S,p);
                                        printf("%d",p->value);
                                    }
                            }
                        else
                            {
                                Pop(S,p);
                                r=p;
                                p=nullptr;
                            }
                    }
            }
}

//TODO:page 144/13 leetcode上

//TODO:page 144/14
typedef struct{
    BiTNode*data[100];
    int front,rear;
}Queue;
int BiTWidth(BiTree T){
    int maxwidth=1;
    int width=1;
    BiTNode*p=nullptr;
    Queue Q;
    Q.front=Q.rear=-1;
    Q.data[++Q.rear]=T;
    int q=0;/*本层最后结点的序号*/
    while(Q.rear!=Q.front)
    {
        if(Q.front!=q)
        {
            p=Q.data[++Q.front];
            if(p->lchild)
                Q.data[++Q.rear]=p->lchild;
            if(p->rchild)
                Q.data[++Q.rear]=p->rchild;
        }
        else
        {
            width=Q.rear-q;
            if(maxwidth<width)
            maxwidth=width;    
                
        }
    }
    return maxwidth;
}

//TODO:page 144/15
void postorder(int pre[],int l1,int r1,int post[],int l2,int r2){
    if(r1-l1==2)
        {
            post[l2]=pre[l1+1];
            post[l2+1]=pre[r1];
            post[r2]=pre[l1];
        }
   else{
    post[r2]=pre[l1];
    postorder(pre,l1+1,l1+(r1-l1)/2,post,l1,l2+(r1-l1)/2-1);
    postorder(pre,l1+(r1-l1)/2+1,r1,post,l2+(r1-l1)/2,r2-1);
   } 
}
//TODO:page 144/17
bool similar(BiTree T1,BiTree T2){
    if(T1==nullptr&&T2==nullptr)
        return true;
    else if(T1==nullptr||T2==nullptr) 
        {
            return false;

        }
        else
        {
            return similar(T1->lchild,T2->lchild)&&similar(T1->rchild,T2->rchild);
        }
}
//TODO:page 144/18
typedef struct ThreadNode/*线索二叉树的定义*/
{
    int data;
    struct ThreadNode*lchild,*rchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree;

//TODO:page 170/04
typedef struct CSNode{
    int data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

int Leaves(CSTree T){
    if(T==nullptr)
        return 0;
    if(T->firstchild==nullptr)
        return 1+Leaves(T->nextsibling);
    return Leaves(T->firstchild)+Leaves(T->nextsibling);
}

//TODO:page 170/05
int heigh(CSTree T){
    if(T==nullptr)
        return 0;
    int left=heigh(T->firstchild);
    int right=heigh(T->nextsibling);
    if(left<right)
        return right+1;
    else
        return left+1;
}

//TODO:page 170/06
CSTree createCSTree_degree(int e[],int degree[],int n){
    //CSNode *pointer=new CSNode[10];
    CSNode*pointer=(CSNode*)malloc(10*sizeof(CSNode));
    int i,j,d,k=0;
    for(i=0;i<n;i++){/*初始化*/
        pointer[i].data=e[i];
        pointer[i].firstchild=pointer[i].nextsibling=nullptr;
    }
    for(i=0;i<n;i++){
        d=degree[i];
        if(d)
        {
            k++;
            pointer[i].firstchild=&pointer[k];
            for(j=2;j<=d;j++){
                k++;
                pointer[k-1].nextsibling=&pointer[k];
            }
        }
    }
    CSTree T=&pointer[0];
    return T;

}
