#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
# define LIST_INIT_SIZE 100
# define LISTINCREMENT 10
# define ElemType int

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

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
    C.elem=A.elem;C.length=++c;C.listsize=A.listsize;
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
