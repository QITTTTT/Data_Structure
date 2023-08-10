# include <stdio.h>
# include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;

bool InitList(LinkList &L)
{
    L=(LNode*)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next=NULL;
    return true;
}

bool ListInsert(LinkList &L,int i,int e)
{
    if(i<1)
        return false;
    LNode *p;
    int j=0;
    p=L;
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL)
        return false;
    LNode *s=(LNode*)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;
}

bool InsertNextNode(LNode *p,int e)
{
    if(p==NULL)
        return false;
    LNode *s=(LNode*)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;
}

bool InsertPriorNode(LNode *p, int e)
{
    if(p==NULL)
        return false;
    LNode *s=(LNode*)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    s->next=p->next;
    p->next=s;
    s->data=p->data;
    p->data=e;
    return true;
}

bool ListDelete(LinkList &L,int i,int &e)
{
    if(i<1)
        return false;
    int j=0;
    LNode *p=L;
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL)
        return false;
    if(p->next==NULL)
        return false;
    LNode *q=p->next;
    e=q->data;
    p->next=q->next;
    free(q);
    return true;
}
bool DeleteNode(LNode *p)
{
    if(p==NULL)
        return false;
    LNode *q=p->next;
    p->data=q->data;
    p->next=q->next;
    free(q);
    return true;
}
LNode *GetElem(LinkList L,int i)
{
    if(i<0)
        return NULL;
    LNode *p;
    int j=0;
    p=L;
    while(p!=NULL&&j<i)
    {
        p=p->next;
        j++;
    }
    return p;
}

LNode *LocateElem(LinkList L,int e)
{
    LNode *p=L->next;
    while(p!=NULL&&p->data!=e)
        p=p->next;
    return p;
}
int length(LinkList L)
{
    int len=0;
    LNode *p=L;
    while(p->next!=NULL)
    {
        len++;
        p=p->next;
    }
    return len;
}

LinkList List_HeadInsert(LinkList &L)
{
    LNode *s;
    int x;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    scanf("%d",&x);
    while(x!=9999)
    {
        s=(LNode*)malloc(sizeof(LNode));
        s->data=x;
        s->next=L->next;
        L->next=s;
        scanf("%d",&x);
    }
    return L;
}

void PrintList(LinkList L)
{
    LNode *p=L->next;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
}

void Output(LinkList L){
    LNode* P=L->next;
    if(P!=nullptr){
        Output(P);
        printf("%d\n",P->data);
    }
    
}

void Delete_Min(LinkList L){
    //找到最小值结点
    LNode *p=L->next->next;
    LNode *q=L->next;
    LNode *m=q;
    int min=L->next->data;
    while (
        p!=nullptr
    )
    {
        if(p->data<min)
           { min=p->data;
           m=q;
           }
        p=p->next;
        q=q->next;
        
    }
    LNode*temp;
    temp=m->next;
    m->next=m->next->next;
    free(temp);

}
int main()
{
    LinkList L;
    InitList(L);
    List_HeadInsert(L);
    PrintList(L);
   // Output(L);
    Delete_Min(L);
    PrintList(L);

    return 0;
   
}