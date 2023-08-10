#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10

typedef struct{
    int data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}

bool Push(SqStack &S,int x){
    if(S.top==MaxSize-1)
        return false;
    S.top=S.top+1;
    S.data[S.top]=x;
    return true;
}

bool Pop(SqStack &S,int &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top--];
    return true;
}

bool GetTop(SqStack S,int &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    return true;
}

//共享栈
typedef struct{
    int data[MaxSize];
    int top0;
    int top1;
}ShStack;


