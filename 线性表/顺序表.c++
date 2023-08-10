#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct
{
    int *data;
    int LMaxSize;
    int length;
}SqList;

void InitSqList (SqList&L)
{
    L.data=(int*)malloc(MaxSize*sizeof(int));
    L.LMaxSize=MaxSize;
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

void IncreaseSize(SqList &L,int len)
{
    int *p=L.data;
    L.data=(int*)malloc((L.LMaxSize+len)*sizeof(int));
    for(int i=0;i<L.length;i++)
        L.data[i]=p[i];
    L.LMaxSize=L.LMaxSize+len;
    free(p);
}

int LocateElem(SqList L,int e)
{
    int i;
    for(i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1;
    return 0;
}
int main()
{
    SqList L;
    InitSqList(L);
    ListInsert(L,1,1);
    printf("%d\n",L.data[0]);
    printf("%d\n",L.LMaxSize);
    IncreaseSize(L,20);
    printf("%d\n",L.LMaxSize);
}