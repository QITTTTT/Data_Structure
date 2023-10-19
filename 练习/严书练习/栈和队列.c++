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
//TODO:--单链队列--队列的链式存储结构
typedef char QElemType;
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
//初始化
Status InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)    exit(OVERFLOW);
    Q.front->next=nullptr;
    return OK;
}
//销毁队列
Status Destroy(LinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }
    return OK;
}
//插入元素
Status EnQueue(LinkQueue &Q,QElemType e){
    QNode*p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)  return OVERFLOW;
    p->data=e;p->next=nullptr;
    Q.rear->next=p;Q.rear=p;
    return OK;
}
//删除队头元素
Status DeQueue(LinkQueue &Q,QElemType &e){
    if(Q.front==Q.rear) return false;
    QueuePtr p=Q.front->next;
    Q.front->next=p->next;
    if(p==Q.rear)   Q.rear=Q.front;
    e=p->data;
    free(p);
    return OK;
}
//****************************************************************************************
//****************************************************************************************
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
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
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
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
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
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
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
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
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
//****************************************************************************************
//******************************************************************************************
//******************************************************************************************
//TODO:离散事件模拟
//TODO:结构定义
typedef struct {
    int ArrivalTime;
    int Duration;
}LQElemType;
typedef struct LQNode{
    LQElemType data;
    struct LQNode *next;
}LQNode,*LQueuePtr;
typedef struct{
    LQueuePtr front;
    LQueuePtr rear;
    int length;
}LLinkQueue;
//初始化
Status InitLQueue(LLinkQueue &Q){
    Q.front=Q.rear=(LQueuePtr)malloc(sizeof(QNode));
    if(!Q.front)    exit(OVERFLOW);
    Q.front->next=nullptr;Q.length=0;
    return OK;
}
//销毁队列
Status LDestroy(LLinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }
    return OK;
}
//插入元素
Status EnLQueue(LLinkQueue &Q,LQElemType e){
    LQNode*p=(LQueuePtr)malloc(sizeof(LQNode));
    if(!p)  return OVERFLOW;
    p->data=e;p->next=nullptr;
    Q.rear->next=p;Q.rear=p;Q.length++;
    return OK;
}
//删除队头元素
Status DeLQueue(LLinkQueue &Q,LQElemType &e){
    if(Q.front==Q.rear) return ERROR;
    LQueuePtr p=Q.front->next;
    Q.front->next=p->next;
    if(p==Q.rear)   Q.rear=Q.front;
    e=p->data;
    free(p);
    Q.length--;
    return OK;
}
Status GetHead(LLinkQueue &Q,LQElemType &e){
    if(Q.front==Q.rear) return ERROR;
    e=Q.front->next->data;
    return OK;
}
typedef struct{
    int OccurTime;
    int NType;
}Event,ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

typedef LinkList EventList;
//变量
EventList ev;
Event en;
LLinkQueue q[5];
LQElemType customer;
int TotalTime,CustomerNum;
int CloseTime=460;
//TODO:函数
int cmp(Event a,Event b){
    if(a.OccurTime<b.OccurTime) return -1;
    else if(a.OccurTime>b.OccurTime)    return 1;
    else return 0;
}
Status OrderInsert(EventList ev,Event a,int (*cmp)(Event,Event)){
    if(ev==nullptr) return ERROR;
    LNode *p=ev;
    while(p->next&&cmp(a,p->next->data)==1) p=p->next;
    LNode *n=(LNode*)malloc(sizeof(LNode));
    n->data=a;n->next=p->next;p->next=n;
    return OK;
}
Status InitList(LinkList &L)
{
    L=(LNode*)malloc(sizeof(LNode));
    if(L==NULL)
        return OVERFLOW;
    L->next=NULL;
    return OK;
}
void Random(int &durtime, int & intertime) {
    durtime = rand() % 20 + 1;       // 办业务时间持续1到20分钟
    intertime = rand() % 10 + 1;     // 下一个顾客到来的时间为间隔1到10分钟
}
int MLQueue(LLinkQueue e[]){
    int min=1;
    for(int i=2;i<5;i++){
        if(e[min].length>e[i].length) min=i;
    }
    return min;
}
void OpenForDay(){
    //初始化操作
    TotalTime=0;CustomerNum=0;
    InitList(ev);
    for(int i=1;i<5;i++) InitLQueue(q[i]);
    en.OccurTime=0;en.NType=0;
    OrderInsert(ev,en,cmp);
}
void CustomerArrived(){
    ++CustomerNum;
    int durtime,intertime;
    Random(durtime,intertime);
    int t=en.OccurTime+intertime;
    if(t<CloseTime) OrderInsert(ev,{t,0},cmp);
    int i=MLQueue(q);
    EnLQueue(q[i],{en.OccurTime,durtime});
    if(q[i].length==1){
        OrderInsert(ev,{en.OccurTime+durtime,i},cmp);
    }
    
}
void CustomerDeparture() {
    int i = en.NType;
    if (DeLQueue(q[i], customer) == ERROR) return;
    TotalTime += en.OccurTime - customer.ArrivalTime;
    if (q[i].length != 0) {
        GetHead(q[i], customer);
        OrderInsert(ev,{ en.OccurTime + customer.Duration, i }, cmp);
    }

}
void Bank_Simulation(){
    OpenForDay();
   while(ev->next){
        en=ev->next->data;printf("发生时间%d,事件类型%d\n",en.OccurTime,en.NType);
        if(en.NType==0) CustomerArrived();
        else {CustomerDeparture();}
        ev=ev->next;
    }
    printf("The average time is %f\n",(float)TotalTime/CustomerNum);
}
int main() {
    Bank_Simulation();
    return 0;
}
//**************************************************************************************
//**************************************************************************************
//之后为课后算法设计题