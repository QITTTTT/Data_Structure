#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef struct
{
    int data[MaxSize];
    int length;
}SqList;

void InitSqList (SqList&L)
{
    L.length=0;
};


bool ListInsert(SqList &L,int i,int e)
{
    int k;
    if(i<1||i>L.length+1)
        return  false;
    if(L.length>=MaxSize)
        return  false;
    for(k=L.length-1;k>=i-1;k--)
        L.data[k+1]=L.data[k];
    L.data[i-1]=e;
    L.length++;
    return true;
}

bool ListDelete(SqList &L,int i,int &e)
{
    int k;
    if(i<1||i>L.length)
        return false;
    e=L.data[i-1];
    for(k=i;k<L.length;k++)
        L.data[k-1]=L.data[k];
    L.length--;
    return true;
}