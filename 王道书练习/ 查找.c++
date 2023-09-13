#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct
{
    int data[MaxSize];
    int LMaxSize;
    int length;
}SqList;//顺序存储结构
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;//链式存储结构
//TODO:256/05
int Binary_Search(SqList ST,int low,int high,int x){
    if(low>high) return 0;
    int mid=(low+high)/2;
    if(ST.data[mid]==x)
        return ST.data[mid];
    else if(ST.data[mid<x]) return Binary_Search(ST,mid+1,high,x);
    return Binary_Search(ST,low,mid-1,x);
}

//TODO:256/06
//顺序结构
int SSearch(SqList &S,int x){
    int p=-1;
       for(int i=0;i<S.length;i++)
           if(S.data[i]==x) p=i;
    if(p==0) return p;
    int temp=S.data[p];
    S.data[p]=S.data[p-1];
    S.data[p-1]=temp;
    return p;
}
//链式结构
LNode* LSearch(LinkList &L,int x){
    LNode* p=L->next, * q=nullptr;
    while(p!=nullptr){
        if(p->data==x){
            if(q==nullptr) 
                return p;
            else{ 
                int temp=x;
                p->data=q->data;
                q->data=x;
            return p;
            }
            }
        q=p;
        p=p->next;
    }
    return p;
}
