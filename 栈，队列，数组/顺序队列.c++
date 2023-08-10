#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct{
    int data[MaxSize];
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.rear=Q.front=0;
}

bool QueueEmpty(SqQueue Q){
    if(Q.rear==Q.front)
    return true;
    else
    return false;
}

bool EnQueue(SqQueue &Q,int x){
    if((Q.rear+1)%MaxSize==Q.front)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q,int &x){
    if(Q.rear==Q.front)
        return false;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    return true;
}

bool GetHead(SqQueue Q,int &x){
    if(Q.rear==Q.front)
        return false;
    x=Q.data[Q.front];
    return true;
}