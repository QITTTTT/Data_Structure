
#include <stdio.h>
#include <stdlib.h>
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
    char s[10];
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
            printf("不是中心对称\n");
            return false;
        }
    }
    printf("是中心对称\n");
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
        printf("共享栈已满\n");
        return false;
    }
    switch(i)
    {
    case 0:S.top[i]+=1;S.data[S.top[i]]=x;break;
    case 1:S.top[i]-=1;S.data[S.top[i]]=x;break;
    default: printf("栈号错误");return false;
    }
    return true;
}

bool Pop(ShStack &S,int i,int &x)
{
    switch(i)
    {case 0:
        if(S.top[0]==-1)
        {
            printf("0号栈已空");
            return false;
        }
        x=S.data[S.top[0]];
        S.top[0]-=1;
        break;
    case 1:
        if(S.top[1]==MaxSize)
        {
            printf("1号栈已空");
            return false;
        }
        x=S.data[S.top[1]];
        S.top[1]+=1;
        break;
    default:printf("栈号错误");return false;
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
        printf("栈已满\n");
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
        printf("栈已空\n");
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
                            printf("工作栈已满\n");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case'[':
                    if(top==MaxSize-1)
                        {
                            printf("工作栈已满\n");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case'{':
                    if(top==MaxSize-1)
                        {
                            printf("工作栈已满\n");
                            return false;
                        }
                    a[++top]=str[i];
                    break;
            case')':
                    if(top==-1)
                        {
                            printf("不匹配\n");
                            return false;
                        }
                    if(a[top]=='(')
                        top--;
                    break;
            case']':
                    if(top==-1)
                        {
                            printf("不匹配\n");
                            return false;
                        }
                    if(a[top]=='[')
                        top--;
                    break;
            case'}':
                    if(top==-1)
                        {
                            printf("不匹配\n");
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
            printf("不匹配\n");
            return false;
        }
    printf("匹配");
    return true;
}
//TODO:page 092/02
//参考严书

//TODO:page 092/03

double P(double x,int n){
    if(n<0) return 0;
    typedef struct PStack{
        int data[100];
        int top;
    }PStack;
    PStack S;S.top=-1;
    double p1=2*x,p2=1;
    if(n==1)    return p1;
    if(n==0)    return p2;
    while(n>1){
        S.data[++S.top]=n--;
    }
    while(S.top>=0){
        int temp=p1;
        p1=2*x*p1-2*(S.data[S.top--]-1)*p2;p2=temp;
    }
    return p1;
}

int main(){
    printf("%f",P(2,2));
    return 0;
}