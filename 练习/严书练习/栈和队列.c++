#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>
#include <cctype>
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef char SElemType;
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
Status Push(SqStack &s, SElemType e) {
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
    if(s.top==s.base)
    return OK;
    else return FALSE;
}

// 读取栈顶元素
Status GetTop(SqStack s, SElemType &e){
    if(s.top==s.base)   return ERROR;
    e=*(s.top-1);
    return OK;
}
//清空
void ClearStack(SqStack &s) {
    while (!StackEmpty(s)) {
        SElemType e; // 假设 SElemType 是栈中元素的类型
        Pop(s, e);   // 使用 Pop 操作弹出栈顶元素，可以根据您的实际定义调用
    }
}
//销毁
void DestroyStack(SqStack &s) {
    if (s.base) {
        // 如果栈的底部指针（base）不为空，表示栈存在
        // 释放栈内元素所占用的内存
        free(s.base);
        s.base = NULL; // 将栈底部指针置为 NULL，表示栈已被销毁
        s.top = NULL;
        s.stacksize = 0;
    }
}

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
Status BracketCheck(char p[],int n){
    SqStack S;
    InitStack(S);
    for(int i=0;i<n;i++){
        if(p[i]=='('||p[i]=='{'||p[i]=='['){
            Push(S,p[i]);
        }else if(StackEmpty(S))
                return FALSE;
        else{
            char e;Pop(S,e);
            switch (p[i])
            {
                case ')':
                    if(e!='(') return FALSE;
                    break; 
                case '}':
                    if(e!='{') return FALSE;
                    break; 
                case ']':   
                    if(e!='[') return FALSE;
                    break;  
            }
        } 
    }
    if(!StackEmpty(S))  return FALSE;
    return OK;
}
//TODO: 行编辑程序
void LineEdit(){
    SqStack S;
    InitStack (S);
    char ch,c;
    ch=getchar();
    while(ch!=EOF){
        while(ch!='\n'){
            switch (ch){
                case '#':
                    Pop(S,c);
                    break;
                case '@':
                    ClearStack(S);
                    break;
                default: Push(S,ch);
            }
            ch=getchar();
        }
        ClearStack(S);
        if(ch!=EOF) ch=getchar();
    }
    DestroyStack(S);
}
//TODO:迷宫问题
typedef int PosType [2];//[0]为横坐标，[1]为纵坐标
typedef int MazeType [10][10];
typedef struct{
    int ord;
    PosType seat;
    int di;
}SMElemType;
typedef struct{
    SMElemType *base;
    SMElemType *top;
    int  stacksize;
}MSqStack;
void InitMStack(MSqStack &s) {
    s.base = (SMElemType*)malloc( STACK_INIT_SIZE* sizeof(SMElemType));
    if (!s.base) {
        exit(EXIT_FAILURE); // 内存分配失败
    }
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
}
Status Push(MSqStack &s, SMElemType e) {
    if (s.top - s.base >= s.stacksize) {
        // 栈满，追加存储空间
        int new_size = s.stacksize * 2;
        SMElemType *new_base = (SMElemType*)realloc(s.base, new_size * sizeof(SMElemType));
        if (!new_base) {
            exit(EXIT_FAILURE); // 内存分配失败
        }
        s.base = new_base;
        s.top = s.base + s.stacksize;
        s.stacksize = new_size;
    }
    *s.top = e;
    ++s.top;
    return OK;
}
Status Pop(MSqStack &s, SMElemType &e) {
    if (s.top == s.base) {
        return ERROR; // 栈空
    }
    --s.top;
    e = *s.top;
    return OK;
}
Status GetTop(MSqStack s, SMElemType &e) {
    if (s.top == s.base) {
        return ERROR; // 栈空
    }
    e = *(s.top - 1); // 获取栈顶元素，不弹出
    return OK;
}
Status StackEmpty(MSqStack &s) {
    if (s.top == s.base) return OK;
    return FALSE;
}

void PrintStack(MSqStack s) {
    MSqStack tempStack; // 用于辅助反转元素顺序的栈
    InitMStack(tempStack);

    // 反转元素顺序，将元素存入 tempStack
    while (!StackEmpty(s)) {
        SMElemType e;
        Pop(s, e);
        Push(tempStack, e);
    }

    // 输出元素，从栈底到栈顶
    while (!StackEmpty(tempStack)) {
        SMElemType outputElem;
        Pop(tempStack, outputElem);
        printf("seat: (%d, %d), di: %d\n", outputElem.seat[0], outputElem.seat[1], outputElem.di);
    }
}

Status MazePath(MazeType Maze, PosType start, PosType end){
    MSqStack S;
    InitMStack(S);
    SMElemType e;
    Maze[start[0]][start[1]]=-1;
    e.ord=1;e.seat[0]=start[0];e.seat[1]=start[1];e.di=0;
    Push(S,e);GetTop(S,e);
    while(!StackEmpty(S)){
        GetTop(S,e);
        SMElemType next;
        if(e.seat[0]==end[0]&&e.seat[1]==end[1])  {  PrintStack(S); return OK;}
        else{
            switch (e.di){
                case 0:
                    next.seat[0]=e.seat[0];next.seat[1]=e.seat[1]-1;
                    break;
                case 1:
                    next.seat[0]=e.seat[0]+1;next.seat[1]=e.seat[1];
                    break;
                case 2:
                    next.seat[0]=e.seat[0];next.seat[1]=e.seat[1]+1;
                    break;
                case 3:
                    next.seat[0]=e.seat[0]-1;next.seat[1]=e.seat[1];
                    break;
            }
            if(Maze[next.seat[0]][next.seat[1]]==0){
                next.ord=e.ord+1;next.di=0;(S.top-1)->di++;Push(S,next);Maze[next.seat[0]][next.seat[1]]=-1;
            }else if(e.di==4)  {Pop(S,e); Maze[e.seat[0]][e.seat[1]]=0;}
                else (S.top-1)->di++;

        }

    }
    return FALSE;
}
//TODO:表达式求值
typedef struct{
    int *base;
    int *top;
    int  stacksize;
}SqStack0;

// 初始化栈
Status InitStack(SqStack0  &s) {
    s.base = new int[STACK_INIT_SIZE];
    if (!s.base) {
        exit(EXIT_FAILURE);
    }
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

// 入栈操作
Status Push(SqStack0 &s, int e) {
    if (s.top - s.base >= s.stacksize) {
        // 栈满，追加存储空间
        int *new_base = new int[s.stacksize + STACKINCREMENT];
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
Status Pop(SqStack0 &s, int &e) {
    if (s.top == s.base) {
        return ERROR;
    }
    --s.top;
    e = *s.top;
    return OK;
}
Status GetTop(SqStack0  s, int &e){
    if(s.top==s.base)   return ERROR;
    e=*(s.top-1);
    return OK;
}
int EvaluateExpression(){
    SqStack OPTR;SqStack0 OPND;char p;int answer;
    InitStack(OPTR);    Push(OPTR,'#');GetTop(OPTR,p);
    InitStack(OPND);    int c=getchar();
    while(c!='#'||p!='#'){
        if(isdigit(c)){
            Push(OPND,c-'0');c=getchar();
        }else{
            switch(c){
                case '+':
                case '-':
                    while(p!='('&&p!='#'){
                        Pop(OPTR,p);
                        int b,a;Pop(OPND,b);Pop(OPND,a);
                        switch(p){
                            case '+':   Push(OPND,a+b);break;
                            case '-':   Push(OPND,a-b);break;
                            case '*':   Push(OPND,a*b);break;
                            case '/':   Push(OPND,a/b);break;
                        }
                        GetTop(OPTR,p);
                    }
                    Push(OPTR,c);GetTop(OPTR,p);c=getchar();
                    break;
                case '*':
                case '/':
                    while(p!='('&&p!='#'&&p!='+'&&p!='-'){
                        Pop(OPTR,p);
                        int b,a;Pop(OPND,b);Pop(OPND,a);
                        switch(p){
                            case '+':   Push(OPND,a+b);break;
                            case '-':   Push(OPND,a-b);break;
                            case '*':   Push(OPND,a*b);break;
                            case '/':   Push(OPND,a/b);break;
                        }
                        GetTop(OPTR,p);
                    }
                    Push(OPTR,c);GetTop(OPTR,p);c=getchar();
                    break;
                case '(':
                    Push(OPTR,c);GetTop(OPTR,p);c=getchar();
                    break;
                case ')':
                    while(p!='('){
                        Pop(OPTR,p);
                        int b,a;Pop(OPND,b);Pop(OPND,a);
                        switch(p){
                            case '+':   Push(OPND,a+b);break;
                            case '-':   Push(OPND,a-b);break;
                            case '*':   Push(OPND,a*b);break;
                            case '/':   Push(OPND,a/b);break;
                        }
                        GetTop(OPTR,p);
                    }
                    Pop(OPTR,p);GetTop(OPTR,p);c=getchar();
                    break;
                case '#':
                    while(p!='#'){
                        Pop(OPTR,p);
                        int b,a;Pop(OPND,b);Pop(OPND,a);
                        switch(p){
                            case '+':   Push(OPND,a+b);break;
                            case '-':   Push(OPND,a-b);break;
                            case '*':   Push(OPND,a*b);break;
                            case '/':   Push(OPND,a/b);break;
                        }
                        GetTop(OPTR,p);
                    }
            }
        }
    }

    GetTop(OPND,answer);
    return answer;
}
//