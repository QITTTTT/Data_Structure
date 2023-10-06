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
