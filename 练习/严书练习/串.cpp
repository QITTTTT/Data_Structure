#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

//TODO:串的定长顺序存储表示
#define MAXSIZE 255
typedef unsigned char SString[MAXSIZE+1];//0号单元存放串的长度
//TODO:串的堆分配存储表示
typedef struct{
    char *ch;
    int length;
}HString;
//TODO:串的块链结构
#define CHUNKSIZE 80
typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;
typedef struct{
    Chunk *head,*tail;
    int curlen;
}LString;
//TODO:KMP
int next[MAXSIZE];
int nextval[MAXSIZE];

//next数组
void get_next(SString T,int (&next)[]){
    next[1]=0;int i=1;int j=0;
    while(i<T[0]){
        if(j==0||T[i]==T[j]){
            i++;j++;next[i]=j;
        }else{
            j=next[j];
        }
    }
}
//使用next数组
int Index_KMP(SString S,SString T,int pos){
    int i=pos,j=1;
    while(i<=S[0]&&j<=T[0]){
        if(S[i]==T[j]){
            i++;j++;
        }else{
            j=next[j];
        }
    }
    if(j>T[0])  return i-T[0];
    else return 0;
}
//nextval数组
void get_nextval(SString T,int (&nextval)[]){
    nextval[1]=0;int i=1;int j=0;
    while(i<T[0]){
        if(j==0||T[i]==T[j]){
            i++;j++;
            T[i]=(T[i]!=T[j]?j:nextval[j]); 
        }else{
            j=nextval[j];
        }
    }
}
//TODO:建立词索引表
//TAG 过于复杂,有时间再实现
#define MaxBookNum 1000     //1000本书
#define MaxKeyNum 2500      //索引表最大容量
#define MaxLineLen 500      //书目串最大长度
#define MaxWordNum 10       //词表的最大容量

typedef struct{
    char *item[MaxWordNum];
    int last;           //词表的长度
}WordListType;  //词表类型

typedef int ElemType;

typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;   //链表类型

typedef struct{
    HString key;
    LinkList bnolist;
}IdxTermType;       //索引项类型

typedef struct{
    IdxTermType item[MaxKeyNum+1];
    int last;       //表长
}IdxListType;       //索引表类型(有序表)

//主要变量
char *buf;
WordListType wdlist;

//TODO:4.10
/*
void Reverse(StringType &s){
    if(StrLength(s)!=0){
        StringType t;StrAssign(t,s);
        StrAssign(s,"0/");
        int i=StrLength;
        while(i>0){
            s=Concat(s,SubString(t,i,1));
            i--;
        }
    }
}
*/
//TODO:4.10
/*
int* Alg_4_10(StringType s,StringType t,StringType &r){
    int *Loc=new int[StrLength(s)];
    for(int i=1;i<=StrLength(s);i++){
        StringType c=SubString(s,i,1);
        int j=1;int tag=0;
        while(j<=StrLength(t)){
            if(StrCompare(c,SubString(t,j,1))==0){tag=1;}
            j++;
        }
        if(tag==0){
            int k=1;
            while(k<=StrLength(r)&&StrCompare(c,SubString(t,k,1))!=0){k++;}
            if(k==StrLength(r)+1){
                r=Concat(r,c);Loc[StrLength(r)-1]=i;
            }
        }

    }
    return Loc;
}
*/
//TODO:4.12
/*
Status Replace(StringType &S,StringType T,StringType V){
    int m=StrLength(S),n=StrLength(T);
    for(int i=1;i<=m-n+1);){
        if(Compare(T,SubString(S,i,n))==0){
            StringType r=SubString(S,1,i-1);
            StringType p=SubString(S,i+n,m);
            S=Concat(r,Concat(V,p));
            m=StrLength(S);
            i+=StrLength(V);
        }else{i++;}
    }
    return OK;
}
*/
//TODO:4.13
/*
void delete_same(StringType &s,StringType t){
    int m=StrLength(s),n=StrLength(t);
    for(int i=1;i<=m-n+1);){
        if(Compare(t,SubString(s,i,n))==0){
            StringType r=SubString(s,1,i-1);
            StringType p=SubString(s,i+n,m);
            s=Concat(r,p);
            m=StrLength(s);
        }else{i++;}
    }
}
*/
//TODO:4.14
/*
typedef struct Stack{
    StringType data[100];
    int top;
}Stack;
StringType Postfix_transform(StringType p){
    Stack S;
    int m=StrLength(p);
    while(m>0){
        if(isdigit(SubString(p,m,1))){
            Push(S,SubString(p,m,1));
        }else{
            StringType x,y;Pop(S,x);Pop(S,y);
            Push(S,Concat(Concat(x,y),SubString(p,m,1)));
        }
        m--;
    }
    return GetTop(S);
}
*/
//TODO:4.15
Status StrAssign(SString &S,char chars[]){
    int i=0;
    while(chars[i]){
        S[i+1]=chars[i];
        i++;
    }
    S[0]=i;
    return OK;
}
//TODO:4.16
Status StrCompare(SString S,SString T){
    if(S[0]==T[0]){
        for(int i=1;i<=S[0];i++){
            if(S[i]>T[i])   return 1;
            if(S[i]<T[i])   return -1; 
        }
    }
    return S[0]-T[0];
}
//TODO:4.17
Status Replace(SString &S,SString T,SString V){
    int i=1;
    while(i<=S[0]-T[0]+1){
        int j=1;int k=i;
        while(j<=T[0]&&T[j]==S[k]){
            j++;k++;
        }
        if(j==T[0]+1){
            int d=T[0]-V[0];
            if(d==0){
                int m=V[0];k--;
                while(m>=1){
                    S[k]=V[m];
                    m--;
                }
                S[0]=S[0]-d;
            }else if(d>0){
                int m=i;
                for(;m-i+1<=V[0];m++){S[m]=V[m-i+1];}
                for(;m<=S[0]-d;m++,k++){S[m]=S[k];}
                S[0]=S[0]-d;
            }else{
                if(V[0]+i-1>=MAXSIZE){
                    for(int l=1;i<=MAXSIZE;l++,i++){S[i]=V[l];}S[0]=MAXSIZE;return OK;
                }else{
                    int m;int n;
                    if(S[0]-d<=MAXSIZE){
                        m=S[0]-d;n=S[0];
                    }else{
                        m=MAXSIZE;n=MAXSIZE+d;
                    }
                    S[0]=m;
                    for(;n>=k;m--,n--){S[m]=S[n];}
                    for(n=V[0];n>=1;n--,m--){S[m]=V[n];}
                    
                }
            }
            
            i=i+V[0];
        }else i++;
    }
    return OK;
}

//TODO:4.18
int* char_kinds(SString S,SString &r){
    r[0]=0;
    int *count=(int *)malloc(S[0]*sizeof(int));count[0]=r[0];
    for(int i=1;i<=S[0];i++){
        int j=1;
        while(j<=r[0]&&r[j]!=S[i]){
            j++;
        }
        if(j<=r[0]){count[j]++;}
        else{r[0]++;r[r[0]]=S[i];count[j]=1;count[0]++;}
    }
    return count;
}
//TODO:4.19
int *difference(SString s,SString t,SString &r){
    r[0]=0;
    int*count=(int*)malloc(sizeof(int)*s[0]);
    for(int si=1;si<=s[0];si++){
        int ti=1;
        while(ti<=t[0]&&t[ti]!=s[si]){
            ti++;
        }
        if(ti>t[0]){
            int ri=1;
            while(ri<=r[0]&&r[ri]!=s[si]){
                ri++;
            }
            if(ri>r[0]){
                r[0]++;count[0]=r[0];r[r[0]]=s[si];count[count[0]]=si;
            }
        }
    }
    return count;
}
//TODO:4.20
void Delete(SString &s,SString t){
    for(int si=1;si<=s[0];si++){
        int ti=1,sj=si;
        while(ti<=t[0]&&t[ti]==s[sj]){
            ti++;sj++;
        }
        if(ti>t[0]){
            for(int i=si;i<=s[0]-t[0];i++){
                s[i]=s[sj];sj++;
            }
            s[0]=s[0]-t[0];si--;
        }
    }
}
//TODO:4.21
//设串类型
typedef struct strNode{
    char chdata;
    strNode *next;
}strNode,*strPtr;
//赋值
strPtr strAssign(char p[]){
    strPtr head=new strNode;head->next=NULL;strNode*r=head;
    int i=0;
    while(p[i]){
        strNode*q=new strNode;q->chdata=p[i];
        q->next=r->next;r->next=q;r=q;
        i++;
    }
    return head;
}
//复制
strPtr StrCopy(strPtr t){
    if(!t)  return NULL;
    strNode *p=t->next;
    strPtr head=new strNode;head->next=NULL;strNode*r=head;
    while(p){
        strNode *q=new strNode;q->chdata=p->chdata;
        q->next=r->next;r->next=q;r=q;
        p=p->next;
    }
    return head;
}
//比较
int StrCompare(strPtr s,strPtr t){
    if(!s||!t)    return INFEASIBLE;
    s=s->next;t=t->next;int tcount=0,scount=0;
    while(s&&t&&s->chdata==t->chdata){
        s=s->next;scount++;
        t=t->next;tcount++;
    }
    return scount-tcount;    
}
int StrLength(strPtr s){
    if(!s)  return INFEASIBLE;
    s=s->next;int scount=0;
    while(s){
        s=s->next;scount++;
    }
    return scount;
}
strPtr Concat(strPtr s,strPtr t){
    if(!s||!t)  return NULL;
    strPtr head=new strNode;head->next=NULL;strNode*r=head;
    while(s->next){
        strNode*p=new strNode;p->chdata=s->next->chdata;
        s=s->next;p->next=r->next;r->next=p;r=p;
    }
    while(t->next){
        strNode*p=new strNode;p->chdata=t->next->chdata;
        t=t->next;p->next=r->next;r->next=p;r=p;
    }
    return head;
}
//子串
strPtr SubString(strPtr s,int start,int len){
    if(!s)  return NULL;
    strPtr head=new strNode;head->next=nullptr;strNode*r=head;
    while(s->next&&start!=0){
        s=s->next;start--;
    }if(start!=0)  return NULL;
    while(s&&len!=0){
        strNode *p=new strNode;p->chdata=s->chdata;
        p->next=r->next;r->next=p;r=p;s=s->next;len--;
    }
    if(len!=0)  return NULL;
    return head;
}
