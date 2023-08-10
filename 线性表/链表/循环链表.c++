#include <stdio.h>
#include <stdlib.h>
//单链表
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;

bool InitList(LinkList &L)
{
    L=(LNode*)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next=L;
    return true;
}

bool Empty(LinkList L)
{
    return(L->next==L);
}







//双链表
typedef struct DNode{
    int data;
    struct DNode *prior,*next;
}DNode, *DLinklist;


bool InitDLinkist(DLinklist &L)
{
    L=(DNode*)malloc(sizeof(DNode));
    if(L==NULL)
        return false;
    L->prior=L;
    L->next=L;
    return true;
}

bool Empty(DLinklist L)
{
    return L->next==L;
}

bool isTail (DLinklist L,DNode *p)
{
    return p->next==L;
}

bool InsertNextDNode(DNode *p,DNode *s)
{
    if(p==NULL||s==NULL)
        return false;
    s->next=p->next;
    s->prior=p;
    p->next->prior=s;
    p->next=s;
    return true;
}