#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;


//TODO:page 67/03/2
bool Judge(char A[]){
    int count=0;
    int i=0;
    while(A[i]!='\0')
    {
        if(A[i]='I')
            count+=1;
        else
            count-=1;
        if(count<0)
        return false;
        i=i+1;
    }
    if(count=0)
        return true;
    else
        return false;
}

//TODO:page 067/04
bool judge(LinkList  L,int n)
{
    int i;
    LNode *p=L->next;
    char s[n/2];
    for(i=0;i<n/2;i++,p=p->next)
    {
        s[i]=p->data;
    }   
    if(n%2!=0)
        p=p->next;
    for(i=n/2-1;i>=0;i--,p=p->next)
    {
        if(s[i]!=p->data)
        {
            printf("%s","不是中心对称");
            return false;
        }
    }
    printf("%s","是中心对称");
    return true;
}
//TODO:page 67/05
#define MaxSize 10

typedef struct{
    int data[MaxSize];
    int top[2];
}ShStack;

void InitStack(ShStack &S){
    S.top[0]=-1;
    S.top[1]=MaxSize;
}

bool Push(ShStack &S,int i,int x)
{
    if(S.top[0]+1==S.top[1])
    {
        printf("%s","共享栈已满");
        return false;
    }
    switch(i)
    {
    case 0:S.top[i]+=1;S.data[S.top[i]]=x;break;
    case 1:S.top[i]-=1;S.data[S.top[i]]=x;break;
    default: printf("%c","栈号错误");return false;
    }
    return true;
}

bool Pop(ShStack &S,int i,int &x)
{
    switch(i)
    {case 0:
        if(S.top[0]==-1)
        {
            printf("%c","0号栈已空");
            return false;
        }
        x=S.data[S.top[0]];
        S.top[0]-=1;
        break;
    case 1:
        if(S.top[1]==MaxSize)
        {
            printf("%c","1号栈已空");
            return false;
        }
        x=S.data[S.top[1]];
        S.top[1]+=1;
        break;
    default:printf("%c","栈号错误");return false;
    }
    return true;
}
//TODO:page 082/01
typedef struct{
    int data[MaxSize];
    int front,rear;
    int tag;    //操作为push，则为1；操作为pop，则为0
}SqQueue;

void InitSqQueue(SqQueue &Q)
{
    Q.rear=Q.front=0;
    int tag=0;
}
bool EnQueue(SqQueue &Q,int e)
{
    if(Q.rear==Q.front&&Q.tag==1)
    {
        printf("%c","栈已满");
        return false;
    }
    Q.data[Q.rear]=e;
    Q.rear=(Q.rear+1)%MaxSize;
    Q.tag=1;
    return true;
}

bool DeQueue(SqQueue &Q,int &e)
{
    if(Q.rear==Q.front&&Q.tag==0)
    {
        printf("%c","栈已空");
        return false;
    }
    e=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    Q.tag=0;
    return true;
}
    
//TODO:page 092/01
bool BracketCheck(char str[])
{
    char a[MaxSize];
    int top=-1,i=0;
    while(str[i]!='\0')
    {
        switch(str[i])
        {
            case '(':
                    if(top==MaxSize-1)
                        {
                            printf("工作栈已满");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case'[':
                    if(top==MaxSize-1)
                        {
                            printf("工作栈已满");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case'{':
                    if(top==MaxSize-1)
                        {
                            printf("工作栈已满");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case')':
                    if(top==-1)
                        {
                            printf("不匹配");
                            return false;
                        }
                    if(a[top]=='(')
                        top--;
                    break;
            case']':
                    if(top==-1)
                        {
                            printf("不匹配");
                            return false;
                        }
                    if(a[top]=='[')
                        top--;
                    break;
            case'}':
                    if(top==-1)
                        {
                            printf("不匹配");
                            return false;
                        }
                    if(a[top]=='{')
                        top--;
                    break;
        }
    i++;
    }
    if(top!=-1)
        {
            printf("不匹配");
            return false;
        }
    printf("匹配");
}

//TODO:page 092/03
double p(int n,double x)
{
    struct stack{
        int no;
        double val;
    }st [MaxSize];
    int top=-1,i;
    int val0=1,val1=2*x;
    for(i=n;i>1;i--)
    {
        st[++top].no=i;
    }
    while(top>=0){
        st[top].val=2*x*val1-2*(i-1)*val1;
        val0=val1;
        val1=st[top].val;
        top--;
    }
   if(n==0)
        return val0;
    else
        return val1; 
}

//TODO:page 093/04

