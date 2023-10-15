#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef int SElemType;
//TODO:顺序栈的操作
typedef struct{
    SElemType *base;
    SElemType *top;
    int  stacksize;
}SqStack;

// 初始化栈
Status InitStack(SqStack &s) {
    s.base = new SElemType[STACK_INIT_SIZE];
    if (!s.base) {
        exit(EXIT_FAILURE);
    }
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

// 入栈操作
Status Push(SqStack &s, SElemType &e) {
    if (s.top - s.base >= s.stacksize) {
        // 栈满，追加存储空间
        SElemType *new_base = new SElemType[s.stacksize + STACKINCREMENT];
        for (int i = 0; i < s.stacksize; i++) {
            new_base[i] = s.base[i];
        }
        delete[] s.base;
        s.base = new_base;
        s.stacksize += STACKINCREMENT;
        s.top = s.base + s.stacksize;
    }
    *s.top = e;
    ++s.top;
    return OK;
}

// 出栈操作
Status Pop(SqStack &s, SElemType &e) {
    if (s.top == s.base) {
        return ERROR;
    }
    --s.top;
    e = *s.top;
    return OK;
}

// 判空操作
Status StackEmpty(SqStack &s) {
    return s.top == s.base;
}

// 释放栈内存


//TODO:数制转换
void conversion(){
    int N;
    SqStack S;
    InitStack(S);
    scanf("%d",&N);
    while(N){
        SElemType e=N%8;
        Push(S,e);
        N=N/8;
    }
    while(!StackEmpty(S)){
        SElemType e;
        Pop(S,e);
        printf("%d",e);
    }
}
//TODO:括号匹配
void BracketCheck(char *p []){
    
}