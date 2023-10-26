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

