#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Status.h"
# define LIST_INIT_SIZE 100
# define LISTINCREMENT 10
# define ElemType char

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
    int freq;
}DuLNode,*DuLinkList;

//TODO:2.10
Status DeleteK(SqList&a,int i,int k){
    if(i<0||k<0||i+k>=a.length)     return INFEASIBLE;
    while(k+i<a.length){
        a.elem[i]=a.elem[i+k];
        i++;
    }
    a.length=a.length-k;
    return OK;
}
//TODO:2.11
Status OrderList(SqList &va,ElemType x){
    if(va.length>=va.listsize){
        ElemType *newbase=(ElemType*)realloc(va.elem,(va.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)    return OVERFLOW;//存储分配失败
        va.elem=newbase;                //新基址
        va.listsize+=LISTINCREMENT;
    }//若线性表已满，则申请增加分配
    int i=0;
    while(i<va.length&&va.elem[i]<=x)   i++;//找到第一个比x大的树
    for(int j=va.length;j>i;j--){
        va.elem[j]=va.elem[j-1];            //后移
    }
    va.elem[i]=x;                           //插入x
    va.length++;
    return OK;
}
//TODO:2.12
Status Compare(SqList A,SqList B){
    if(A.length==B.length){//若A，B表长相等
        int i=0;
        while(i<A.length&&A.elem[i]==B.elem[i])   i++;
        if(i==A.length) return 0;
        else   return A.elem[i]<B.elem[i]? -1:1; 
    }
    else{                  //表长不相等
        int i=0;                                 //指标
        int min_length=A.length<B.length? A.length:B.length;    //记录最小表长
        while(i<min_length&&A.elem[i]==B.elem[i])   i++;        //找到第一个不相等的元素
        if(i==min_length)   return A.length<B.length? -1:1;
        else    return A.elem[i]<B.elem[i]? -1:1; 
    }
}
//TODO:2.13
int LOCATE(SqList L,int X){
    for(int i=0;i<L.length;i++){
        if(L.elem[i]==X)   return i+1;
    }
    return ERROR;
}
//TODO:2.14
int LENGTH(LinkList L){
    int count=0;
    while(L->next){
        count++;
        L=L->next;
    }
    return count;
}
//TODO:2.15
Status CONNECT(LinkList &ha,LinkList &hb,LinkList &hc){
    LNode*temp=LENGTH(ha)<LENGTH(hb)?ha->next:hb->next;
    hc->next=temp;
    while(temp->next)   temp=temp->next;
    temp->next=LENGTH(ha)<LENGTH(hb)?hb->next:ha->next;
    free(ha);free(hb);
    return OK;
}
//TODO:2.16
Status DeleteAndInsertSub(LinkList &la,LinkList &lb,int i,int j,int len){
    //入口判断
    if(i<=0||j<=0||len<0)   return INFEASIBLE;
    //删除len个元素
    if(i==1){
        LNode*temp=la;int tcount =1;
        while(la&&tcount<=len){
            temp=la;la=la->next;tcount++;
            free(temp);
        }
        if(tcount<=len) return INFEASIBLE;
    }
    else{
        LNode*p=la;int pcount=1;//la的第i-1个元素
        while(p->next&&pcount<i-1){
            p=p->next;
            pcount++;
        }
        if(pcount<i-1||!p) return INFEASIBLE;
        LNode*temp=p->next;int tcount=1;
        while(temp&&tcount<=len){
            p->next=temp->next;
            free(temp);
            temp=p->next;tcount++;
        }
        if(tcount<=len) return INFEASIBLE;
    };
    //插入
    if(j==1){
        LNode*temp=la;
        while(temp->next)   temp=temp->next;
        temp->next=lb;lb=la;
        return OK;
    }
    else{
        LNode*q=lb;int qcount=1;//lb的第j-1个元素
        while(q->next&&qcount<j-1){
            q=q->next;
            qcount++;
        }
        if(qcount<j-1||!q) return INFEASIBLE;
        LNode*temp=la;
        while(temp->next)   temp=temp->next;
        temp->next=q->next;q->next=la;
        return OK;
    }
}

//TODO:2.17
Status HEADINSERT(LinkList&L,int i,ElemType b){
    LNode*q=(LNode*)malloc(sizeof(LNode));
    if(!q)  return OVERFLOW;
    q->data=b;
    if(i==1){
        q->next=L;L=q;
    }
    else{
        LNode*p=L;int count=1;
        while(p->next&&count<i-1){//找到第i-1个结点
            p=p->next;count++;
        }
        if(count<i-1)   return INFEASIBLE;
        q->next=p->next;p->next=q;
        }
    return OK;
}
//TODO:2.18
Status DELETE(LinkList &L, int i, ElemType &e){
    LNode*q=L;int count=1;
    while(q->next&&count<i-1){q=q->next;count++;}//找到第i-1个元素
    if(!q||!q->next)    return INFEASIBLE;      //没有第i个元素
    if(i==1){
        LNode*temp=L;
        L=L->next;
        e=temp->data;free(temp);
    }else{
        LNode*temp=q->next;
        e=temp->data;q->next=temp->next;free(temp);
    }
    return OK;
}
//TODO:2.19
Status RANGEDELETE(LinkList&L,int mink,int maxk){
    if(mink>=maxk)  return INFEASIBLE;
    LNode*p=L;
    for(LNode* temp=p->next;temp;){
        if(temp->data>mink&&temp->data<maxk){
            p->next=temp->next;free(temp);temp=p->next;
        }else{
            p=p->next;temp=p->next;
        }
    }
    return OK;
}
//TODO:2.20
Status SAMEDELETE(LinkList &L){
    for(LNode*p=L->next,*temp=p->next;p->next;){
        if(p->data==temp->data){
            p->next=temp->next;
            free(temp);temp=p->next;
        }else{
            p=p->next;temp=temp->next;
        }
    }
    return OK;
}
//TODO:2.21
Status SINVERSION(SqList &A){
    for(int i=0,j=A.length-1;i<=A.length/2-1;i++,j--){
        ElemType temp=A.elem[i];
        A.elem[i]=A.elem[j];
        A.elem[j]=temp;
    }
    return OK;
}
//TODO:2.22
Status LINVERSION(LinkList &L){
    if(L->next==nullptr||L->next->next==nullptr)    return OK;
    LNode*p=L->next,*q=p->next,*r=q->next;
    p->next=nullptr;
    for(;r;p=q,q=r,r=r->next){
        q->next=p;
    }
    q->next=p;
    L->next=q;
    return OK;
}
//TODO:2.23
Status Merge(LinkList &A,LinkList &B,LinkList &C){
    LNode*p=A->next,*q=B->next,*r=C;        //处理结点
    LNode*pn=p->next,*qn=q->next;
    while(p&&q){
        r->next=p;r=r->next;
        r->next=q;r=r->next;
        p=pn;if(pn)pn=pn->next;
        q=qn;if(qn)qn=qn->next;
    }
    if(q)    r->next=q;
    if(p)    r->next=p;
    A->next=nullptr;B->next=nullptr;
    return OK;
}

//TODO:2.24
Status InversionMerge(LinkList &A,LinkList &B,LinkList &C){
    LNode*p=A->next,*q=B->next,*r=C;        //当前处理结点
    LNode*pn=p->next,*qn=q->next;           //记录当前处理节点的后继结点
    while(p&&q){                            //AB均有未处理结点
        if(p->data<=q->data){
            p->next=r->next;r->next=p;
            p=pn;if(pn) pn=pn->next;
        }else{
            q->next=r->next;r->next=q;
            q=qn;if(qn) qn=qn->next;
        }
         
    }
    while(p){
            p->next=r->next;r->next=p;
            p=pn;if(pn) pn=pn->next;
        }
    while(q){
            q->next=r->next;r->next=q;
            q=qn;if(qn) qn=qn->next;
        }
        A->next=nullptr;B->next=nullptr;  
    return OK;
}
//TODO:2.25
Status Intersection(SqList A,SqList B,SqList &C){
    int k=0;
    for(int i=0,j=0;i<A.length&&j<B.length;){
        if(A.elem[i]<B.elem[j]) i++;
        else if(A.elem[i]>B.elem[j])    j++;
            else {
                if(C.length==C.listsize){
                    ElemType *newbase=(ElemType*)realloc(C.elem,(C.listsize+LISTINCREMENT)*sizeof(ElemType));
                    if(!newbase)    return OVERFLOW;
                    C.elem=newbase;
                    C.length+=LISTINCREMENT;
                }    
                C.elem[k]=A.elem[i];
                i++;j++;k++;
            }
    }
    return k;
}
//TODO:2.26
Status INTERSECTION(LinkList A,LinkList B,LinkList C){
    for(LNode*p=A->next,*q=B->next,*r=C;p&&q;){
        if(p->data<q->data) p=p->next;
        else if(p->data>q->data)    q=q->next;
            else{
                LNode *n=(LNode*)malloc(sizeof(LNode));
                n->data=p->data;r->next=n;r=r->next;
                p=p->next;q=q->next;
            }
    }
    return OK;
}
//TODO:2.27
Status Intersectionplus(SqList &A,SqList &B,SqList &C){
    int c=-1;        //用于存放C的元素
    for(int i=0,j=0;i<A.length&&j<B.length;){       //扫描A，B
        if(A.elem[i]<B.elem[j]) i++;
        else if(A.elem[i]>B.elem[j])    j++;
            else {
                if(c==-1)  A.elem[++c]=A.elem[i];
                if(A.elem[i]!=A.elem[c]){
                    A.elem[++c]=A.elem[i];
                }
                i++;j++;
            }
    }
    C.elem=A.elem;C.length=c+1;C.listsize=A.listsize;
    return OK;
}
//TODO:2.28
Status INTERSECTIONPLUS(LinkList &A,LinkList &B,LinkList &C){
    int tag=0;LNode*r=A;
    for(LNode*p=A->next,*q=B->next;p&&q;){
        if(p->data<q->data) p=p->next;
        else if(p->data>q->data)    q=q->next;
            else{
                if(tag==0){
                    r=r->next;r->data=p->data;tag=1;
                }else{
                    if(r->data!=p->data){
                        r=r->next;r->data=p->data;
                    }
                }
                p=p->next;q=q->next;
            }
    }
    LNode*temp=r->next;r->next=nullptr;
    while(temp){
        r=temp;temp=temp->next;free(r);
    }
    C->next=A->next;free(A);A=r=nullptr;
    return OK;
}
//TODO:2.29
Status Alg_2_29(SqList &A,SqList B,SqList C){
    SqList D;
    D.elem=nullptr;D.length=D.listsize=0;
    Intersectionplus(B,C,D);     //D是BC的交集
    int k=-1,i=0;        //结果表的末尾元素的索引
    for(int j=0;j<D.length;){
        if(A.elem[i]<D.elem[j]) A.elem[++k]=A.elem[i++];
        else if(A.elem[i]>D.elem[j])  j++;
        else    i++;
    }
    while(i<A.length){A.elem[++k]=A.elem[i++];}
    A.length=k+1;
    return OK;
}
//TODO:2.30
Status Alg_2_30(LinkList &A,LinkList &B,LinkList &C){
    LinkList D=(LNode*)malloc(sizeof(LNode));
    if(!D)  return OVERFLOW;
    INTERSECTIONPLUS(B,C,D);
    LNode*r=A,*p=A->next;
    for(LNode*q=D->next;q;){
        if(p->data<q->data){r=r->next;r->data=p->data;p=p->next;}
        else if(p->data>q->data)  q=q->next;
        else p=p->next;
    }
    while(p){
        r=r->next;r->data=p->data;p=p->next;
    }
    LNode*temp=r->next;r->next=nullptr;
    while(temp){
        r=temp;temp=temp->next;free(r);
    }
    return OK;
}
//TODO:2.31
Status DeletePrior(LNode*s){
    LNode*p=s,*temp=nullptr;
    while(p->next->next!=s) p=p->next;
    temp=p->next;p->next=temp->next;free(temp);
    return OK;
}
//TODO:2.32
typedef struct LNodex{
    ElemType data;
    struct LNodex *next;
    struct LNodex *prior;
}LNodex,*LinkListx;
Status DoubleLinked(LinkListx &L){
    LNodex*p=L;LNodex*q=L->next;
    do{
        q->prior=p;p=q;q=q->next;
    }while(q!=L->next);
    return OK;
}
//TODO:2.33
Status Divide(LinkList &A,LinkList letters,LinkList digits,LinkList others){
    LNode*p=A->next;
    while(p!=A){
        if(isalpha(p->data)){
            A->next=p->next;p->next=letters->next;letters->next=p;
        }else if(isdigit(p->data)){
            A->next=p->next;p->next=digits->next;digits->next=p;
        }else{
            A->next=p->next;p->next=others->next;others->next=p;
        }
        p=A->next;
    }
    free(A);A=nullptr;
    return OK;
}
//TODO:2.34~2.36中类型定义
typedef struct XorNode{
    char data;
    struct XorNode *LRPtr;
}XorNode, *XorPointer; 

typedef struct{              //无头结点的异或指针双向链表
    XorPointer Left, Right;  //分别指向链表的左端和右端
}XorLinkedList; 

XorPointer XorP(XorPointer p, XorPointer q){
    XorPointer result;
    result = (XorPointer)((uintptr_t)(p) ^ (uintptr_t)(q));
    return result;
}; //指针异或函数XorP返回指针p和q的异或(XOR)值

//TODO:2.34
Status PRINT(XorLinkedList L){
    XorNode *p=L.Left;XorNode *q=nullptr,*r=p;//p是当前处理结点，q是前驱结点，r用来记录p以更新q
    while(p!=L.Right){
        printf("%c",p->data);
        p=XorP(p->LRPtr,q);
        q=r;r=p;
    }
    printf("%c",p->data);
    return OK;
}
//TODO:2.35
Status INSERT(XorLinkedList &L,int i,char e){
    if(i<1) return INFEASIBLE;
    XorNode *p=L.Left;XorNode *q=nullptr,*r=p;//p是当前处理结点，q是前驱结点，r用来记录p以更新q
    int k=1;                                  //记录p的位序
    while(k!=i){
        p=XorP(p->LRPtr,q);
        q=r;r=p;
        k++;
        if(!p) return INFEASIBLE;
    }
    XorNode *newnode=new XorNode{e,XorP(p,q)};
    p->LRPtr=XorP(XorP(p->LRPtr,q),newnode);
    if(i==1)    L.Left=newnode;
    else q->LRPtr=XorP(XorP(q->LRPtr,p),newnode);
    
    return OK;
}
//TODO:2.36
Status DELETE(XorLinkedList &L,int i,char &e){
    if(i<1) return INFEASIBLE;
    XorNode *p=L.Left,*q=nullptr,*s=XorP(p->LRPtr,q),*r=p;//p是当前处理结点，q是前驱结点，r用来记录p以更新q，s指向后继结点
    int k=1;        //p结点的位序
    while(k!=i){
        p=XorP(p->LRPtr,q);
        q=r;r=p;
        k++;
        if(!p) return INFEASIBLE;
    }
    if(p==L.Left)   { s->LRPtr=XorP(s->LRPtr,p);L.Left=s;delete p;}
    else if(p==L.Right){  q->LRPtr=XorP(q->LRPtr,p);L.Right=q;delete p;  }
    else{
        s->LRPtr=XorP(XorP(s->LRPtr,p),q);
        q->LRPtr=XorP(XorP(q->LRPtr,p),s);
        delete p;
    }
    return OK;

}
//TODO:2.38
Status LOCATE(DuLinkList L,ElemType x){
    DuLNode*p=L->next;DuLNode*r=nullptr;
    while(p!=L&&p->data!=x){
        p=p->next;
    }
    if(p==L){printf("没有此元素");return INFEASIBLE;}
    p->freq++;
    r=p;
    while(r!=L&&r->freq<=p->freq){
        r=r->prior;
    }
    if(r->next!=p){
        p->prior->next=p->next;
        p->next->prior=p->prior;
        p->next=r->next;p->prior=r;p->next->prior=p;r->next=p;
    }
    return OK;
}
//TODO:2.39~2.40稀疏多项式定义
typedef struct{
    int coef;
    int exp;
}PolyTerm;

typedef struct{     //多项式的顺序存储结构
    PolyTerm *data;
    int length;
}SqPoly;

//TODO:2.39
Status Calculate(SqPoly L,int x){
    int sum=0;int xp=1;
    for(int j=0;j<L.length;j++){
        int k;
        if(j==0){
            k=L.data[j].exp;
        }else{
            k=L.data[j].exp-L.data[j-1].exp;
        }
        for(int i=0;i<k;i++){
                xp*=x;
            }
        sum+=L.data[j].coef*xp;
    }
    return sum;
}
//TODO:2.40
Status SUBTRUCT(SqPoly R,SqPoly Q,SqPoly &P){
    
    P.data=new PolyTerm[R.length+Q.length];
    int i=0,j=0,k=0;
    for(;i<R.length&&j<Q.length;){
        if(R.data[i].exp<Q.data[j].exp) {
            P.data[k]=R.data[i];
            i++;
            k++;
        }
        else if(Q.data[j].exp<R.data[i].exp){
            P.data[k].exp=Q.data[j].exp;
            P.data[k].coef=-Q.data[j].coef;
            j++;
            k++;
        }else{
            P.data[k].coef=R.data[i].coef-Q.data[j].coef;
            P.data[k].exp=R.data[i].exp;
            i++;j++;k++;
        } 
    }
    if(i<R.length){
            for(;i<R.length;i++){
                P.data[k]=R.data[i];
                k++;    
            }
        }
    if(j<Q.length){
        for(;j<Q.length;j++){
            P.data[k].exp=Q.data[j].exp;
            P.data[k].coef=-Q.data[j].coef;
            k++;
        }
        }
    P.length=k;
    return OK;
}
