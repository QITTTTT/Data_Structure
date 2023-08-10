#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10

typedef struct{
    char data[MaxSize];
    char top;
}SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}

bool Push(SqStack &S,char x){
    if(S.top==MaxSize-1)
        return false;
    S.top=S.top+1;
    S.data[S.top]=x;
    return true;
}

bool Pop(SqStack &S,char &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top--];
    return true;
}

bool GetTop(SqStack S,char &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    return true;
}
bool StackEmpty(SqStack S){
    if(S.top==-1)
        return true;
    else
        return false;
}

//括号匹配
bool bracketCheck(char str[],int length)
{
    SqStack S;
    InitStack(S);
    for(char i=0;i<length;i++)
    {
        if(str[i]=='('||str[i]=='{'||str[i]=='[')
            Push(S,str[i]);
        else if(StackEmpty(S))
                return false;
            else
                {
                    char topElem;
                    Pop(S,topElem);
                    if(str[i]=='('&&topElem!=')')
                        return false;
                    if(str[i]=='['&&topElem!=']')
                        return false;
                    if(str[i]=='{'&&topElem!='}')
                        return false;
                        
                }
    }
    return(StackEmpty(S));
}

//练习不用基础操作










//表达式求值
