# include<stdlib.h>
# include<stdio.h>

typedef struct DNode{
    int data;
    struct DNode *prior,*next;
}DNode, *DLinklist;

bool InitDLinkist(DLinklist &L)
{
    L=(DNode*)malloc(sizeof(DNode));
    if(L==NULL)
        return false;
    L->prior=NULL;
    L->next=NULL;
    return true;
}

bool empty(DLinklist L)
{
    return L->next==NULL;
}
bool InsertNextDNode(DNode *p,DNode *s)
{
    if(p==NULL||s==NULL)
        return false;
    s->next=p->next;
    if(p->next!=NULL)
        p->next->prior=s;
    s->prior=p;
    p->next=s;
    return true;
}
bool DeleteNextDNode(DNode *p)
{
    if(p==NULL)
        return false;
    DNode *q=p->next;
    if(q==NULL)
        return false;
    p->next=q->next;
    if(q->next!=NULL)
        q->next->prior=p;
    free(q);
    return true;
}