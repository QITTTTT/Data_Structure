#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MaxSize 10
typedef struct
{
    int data[MaxSize];
    int LMaxSize;
    int length;
}SqList;

//TODO:page 017/1
bool DeleteMinElem(SqList &L, int &e)
{
    if(L.length==0) 
        return false;
    e = L.data[0];
    int k=0;
    for(int i=1;i<L.length;i++){
        if(e<L.data[i]){
        e=L.data[i];
        k=i;   
        }
        
    }
    L.data[k]=e;
    return true;
}

//TODO:page 017/2
bool Reverse(SqList L){
    if(L.length==0)
    return false;
    int temp;
    for(int i=0,k=L.length;i=k;i++,k--){
        temp = L.data[i];
        L.data[i] = L.data[k];
        L.data[k] = temp;
    }
    return true;
}

//TODO:page 017/7
bool Merge(SqList L1,SqList L2, SqList &L){
    if(L1.length+L2.length>L.LMaxSize)
    return false;
    int m=0,k,i;
    for(i=0,k=0;i<L1.length&&k<L2.length;m++){
        if(L1.data[i]<L2.data[k])
            {
            L.data[m]=L1.data[i];
            i++;
            }
        else
            {
            L.data[m]=L2.data[k];
            k++;
            }
    }
    while(i<L1.length)
    L.data[m++]=L1.data[i++];
    while(k<L2.length)
    L.data[m++]=L2.data[k++];

    L.length=m;
    return true;
}

//TODO:page 017/8
bool Reverse(int A[],int left,int right,int arraysize)
{
    if(left>right||right>arraysize)
    return false;
    int temp;
    for(int i=0;i<(-left+right)/2;i++)
    {
        temp=A[left+i-1];
        A[left+i-1]=A[right-i-1];
        A[right-i-1]=temp;
    }
    return true;
}
bool Exchange(int A[],int m,int n)
{
    Reverse(A,1,m+n,m+n);
    Reverse(A,1,n,m+n);
    Reverse(A,n+1,m+n,m+n);
    printf("%d\n",A[0]);
    return true;

}

//TODO:page 017/9
void Do(SqList &L,int x){
    int k;
    for(int i=0;i<L.length;i++)
    {
        if(x<L.data[i])
        {
            if(x=L.data[i-1])
            k=i-1;
            else 
            {
                for(k=L.length;k>i;k--){
                    L.data[k]=L.data[k-1];
                }
                L.data[k]=x;

            }
        }
        
    }
    L.data[L.length]=x;
}

//TODO:page 017/10
void Reverse(int R[],int start,int ending)
{
    int temp;
    for(int i=0;i<=(ending-start)/2;i++)
    {
        temp=R[i+start];
        R[i+start]=R[ending-i];
        R[ending-i]=temp;
    }
}

void Converse(int R[],int n,int p)
{
    Reverse(R,0,n-1);
    Reverse(R,0,n-p+1);
    Reverse(R,n-p,n-1);

}

//TODO:page 017/11
int MidSearch(int A[],int B[],int n)
{
    int s1=0,d1=n-1,m1,s2=0,d2=n-1,m2;
    while (s1!=d1||s2!=d2)
    {
        m1=(s1+d1)/2;
        m2=(s2+d2)/2;
        if(A[m1]=B[m2])
        return A[m1];
        if(A[m1]<B[m2])
        {
            if((s1+d1)%2==0){
                s1=m1;
                d2=m2;
            }
            else{
                s1=m1+1;
                d2=m2;
            }
        }
        else{
            if((s2+d2)%2==0){
                d1=m1;
                s2=m2+1;
            }
            else{
                d1=m1;
                s2=m2+1;
            }
        }
    }
    return A[s1]<B[s2]? A[s1]:B[s2];
}
//TODO:page 017/12
int MAINELEM(int A[],int n){
    int B[n];int max=0;
    for(int i=0;i<n;i++)    B[i]=0;
    for(int i=0;i<n;i++){
        B[A[i]]++;
    }
    for(int i=0;i<n;i++){
        if(B[i]>B[max]){
            max=i;
        }
    }
    if(B[max]>n/2)  return max;
    else return 0;
}
//TODO:page 018/13
int Unexistentelem(int A[], int n){
    int B[n];int elem;
    for(int i=0;i<n;i++)    B[i]=0;
    for(int i=0;i<n;i++){
        B[A[i]]=1;
    }
    for(elem=0;elem<n&&B[elem]!=0;elem++){}
    return elem;
}
//TODO:page 018/14
/*每次让最小的元素所在数组下标加一*/

//TODO:page 038/01
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;

bool Delete_x(LinkList &L,int x){
    if(L==NULL)
    return false;
    while(L->data==x )
    {
        LinkList temp = L;
        L=L->next;
        free(temp);
    }
    LinkList k=L;
    for(LinkList i=L->next;i->next!=NULL;i=i->next,k=k->next){
        if(i->data=x)
        {
            k->next=i->next;
            free(i);
        }
    }
    return true;
}

//TODO:page 038/02
bool delete_x(LinkList &L,int x){
    if(L->next==nullptr){
        return false;
    }
    LNode *k;
    for(LinkList p=L->next,q=L;p!=nullptr;p=p->next,q=q->next){
        if(p->data==x){
            k=p;
            q->next=p->next;
            free(k);
        }
    }
    return true;
}
//TODO:page 038/03
void Output(LinkList L){
    LNode* P=L->next;
    while(P!=nullptr){
        Output(P);
        printf("%c\n",P->data);
    }
    
}
//TODO:page 038/04
void Delete_Min(LinkList L){
    //找到最小值结点
    LNode *p=L->next->next;
    LNode *q=L->next;
    LNode *m=q;
    int min=L->next->data;
    while (p!=nullptr)
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

//TODO:page 038/05

// 解法1：
void Reverse_1(LinkList L){
    LNode* P=L->next;
    L->next=nullptr;
    LNode *q=P->next;
    while(P!=nullptr)
    {
        P->next=L->next;
        L->next=P;
        P=q;
        q=q->next;
    }

    }
    
//解法2：
LinkList Reverse_2(LinkList L){
    LNode*pre,* p=L->next,*r=L->next->next;
    p->next=nullptr;
    while (r!=nullptr)
    {
        pre=p;
        p=r;
        p->next=pre;
        r=r->next;
    }
    L->next=p;
    return L;
}
//TODO:page 038/06

//TODO:page 038/07
LinkList Delete(LinkList &L,int m,int n){
    if(m>=n)
    return nullptr;
    LinkList p=L;
    LinkList q=L->next;
    while(q!=nullptr)
    {
        if(m<q->data<n)
        {
            p->next=q->next;
            free(q);
            q=p->next;
        }
        else{
            p=q;
            q=q->next;
        }
    }
    return p;
}
//TODO:page 038/8
LinkList Search_1st_Commom(LinkList L1,LinkList L2){
    int Length1=0,Length2=0;
    LNode *p=L1,*q=L2;
    while(p->next!=nullptr)
    {
        Length1++;
        p=p->next;
    }
    while(q->next!=nullptr)
    {
        Length2++;
        q=q->next;
    }
    int dist=Length1-Length2;
    if(dist>0)
    {
        while(dist>0)
        {
            p=p->next;
            dist--;
        }
    }
    else{
        dist=abs(dist);
        while(dist>0)
        {
            q=q->next;
            dist--;
        }
    }
    while(p!=q)
    {
        p=p->next;
        q=q->next;
        if(p=nullptr)
        return nullptr;
    }
return p;
}

//TODO:page 038/10
LinkList Seperate(LinkList &A)
{
    int count=0;
    LNode *p=A->next,*q=A;
    LinkList B=(LinkList)malloc(sizeof(LNode));
    B->next=nullptr;
    LNode *m=B;
    while(p!=nullptr)
    {
        count++;
        if(count%2==0)
        {
            m->next=p;
            m=p;
        }
        else{
            q->next=p;
            q=p;

        }
    p=p->next;

    }
    m->next=nullptr;
    p->next=nullptr;
    return B;
}

//TODO:page 38/11
LinkList Divide(LinkList &A){
    if(A->next==nullptr)
    return nullptr;
    LinkList B=new(LNode);
    B->next=nullptr;
    LNode *p=A,*q=nullptr,*r=A->next;
    while(r!=nullptr)
    {
        p->next=r;
        r=r->next;
        p=p->next;
        if(r!=nullptr)
        {
          q=r->next;
        r->next=B->next;
        B->next=r;
        r=q;  
        }
    }
    p->next=nullptr;
    return B;
}

//TODO:page 38/12
bool Del_same(LinkList &L)
{
    if(L->next==nullptr)
    return false;
    LNode *p=L->next;
    LNode *q=p->next;
    while(q!=nullptr)
    {
        if(p->data==q->data)
        {
            p->next=q->next;
            free(q);
            q=p->next;
        }
        else{
            p=p->next;
            q=p->next;
        }
    }
    return true;
}

//TODO:page 039/13
void MergeList(LinkList &La,LinkList &Lb)
{
    LNode *r,*pa=La->next,*pb=Lb->next;
    La->next=nullptr;
    while(pa&&pb)
    {
        if(pa->data<=pb->data){
            r=pa->next;
            pa->next=La->next;
            La->next=pa;
            pa=r;
        }
        else
        {
            r=pb->next;
            pb->next=La->next;
            La->next=pb;
            pb=r;
        }
    }
    if(pa)
        pb=pb;
    while(pb){
        r=pb->next;
        pb->next=La->next;
        La->next=pb;
        pb=r;
    }
    free(Lb);
    Lb=nullptr;
}

//TODO:page 39/14
LinkList Get_Common(LinkList A,LinkList B)
{
    LinkList C=(LinkList)malloc(sizeof(LNode));
    C->next=nullptr;
    LNode *ra=A->next,*rb=B->next;
    while(ra&&rb)
    {
        if(ra->data==rb->data)
        {
            LNode *r=(LNode*)malloc(sizeof(LNode));
            r->data=ra->data;
            r->next=C->next;
            C->next=r;
            ra=ra->next;
            rb=rb->next;
        }
        else if(ra->data<rb->data)
                ra=ra->next;
            else
                rb=rb->next;
    }
    return C;
}
//TODO:page 39/15
bool Get_common(LinkList &A,LinkList &B)
{
    if(A==nullptr&&B==nullptr)
    return false;
    LNode *p=A;
    LNode *ra=A->next;
    LNode *rb=B->next;
    while(ra&&rb)
    {
        if(ra->data==rb->data)
        {
            ra=ra->next;
            p=p->next;
            B->next=rb->next;
            rb=B->next;
            free(rb);
            
        }
        else if(ra->data<rb->data)
                {
                p->next=ra->next;
                free(ra);
                ra=p->next;
                }
            else
                {B->next=rb->next;
                free(rb);
                rb=B->next;}
    }
    while(ra)
    {
        p->next=ra->next;
        free(ra);
        ra=p->next;
    }
    while(rb)
    {
        B->next=rb->next;
        free(rb);
        rb=B->next;
    }
    free(B);

    return true;
}
//TODO:page 039/17
typedef struct DNode{
    int data;
    struct DNode *prior,*next;
}DNode, *DLinkList;


bool symmetry(DLinkList L)
{
    DNode*p=L->next;
    DNode*q=L->prior;
    while(q!=p&&p->next!=q)
    {
        if(q->data==q->data)
        {q=q->prior;
        p=p->next;}
        else
        return 0;
    }
    return 1;
}
//TODO:page 39/18
