#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define ElemType int
//二叉树的顺序存储
struct TreeNode{
    ElemType value;
    bool isEmpty;
};
TreeNode t[MaxSize];
//二叉树的链式存储
typedef struct BiTNode{
    ElemType data;
    struct BiTNode*lchild,*rchild;
}BiTNode,*BiTree; 
//先序遍历
void visit(BiTNode* T){
    if(T!=nullptr)
    printf("%d",T->data);
}

void PreOrder(BiTree T){
    if(T!=nullptr)
    {visit(T);
    PreOrder(T->lchild);
    PreOrder(T->rchild);}
}
//层序遍历
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

void LevelOrder(BiTree T){
    LinkQueue Q;
    InitQueue (Q);
    BiTNode *p;
    while(!IsEmpty(Q)){
        EnQueue(Q,p);
        visit(p);
        if(p->lchild!=nullptr)
            EnQueue(Q,p->lchild);
        if(p->rchild!=nullptr)
            EnQueue(Q,p->rchild);
    }

}
//线索二叉树
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode*lchild,*rchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree; 
ThreadNode *pre=nullptr;
void CreateInThead(ThreadTree T){
    pre=nullptr;
    if(T!=nullptr){
        InThread(T);
        if(pre->rchild==nullptr)
            pre->rtag=1;
    }
}
void InThread(ThreadTree T){
    if(T!=nullptr){
        InThread(T->lchild);
        visit(T);
        InThread(T->rchild);
    }
}
void visit(ThreadNode*q){
    if(q->lchild==nullptr){
        q->lchild=pre;
        q->ltag=1;
    }
    if(pre!=nullptr&&pre->rchild==nullptr){
        pre->rchild=q;
        pre->rtag=1;
    }
    pre=q;
}