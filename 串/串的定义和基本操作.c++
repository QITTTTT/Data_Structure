#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN];
    int length;
}SString;

typedef struct{
    char *ch;
    int length;
}HString;
typedef struct StringNode{
    char ch[4];
    struct StringNode *next;
}StringNode,*String;
//找子串
bool SubString(SString &Sub,SString S,int pos,int len){
    if(pos+len-1>S.length)
        return false;
    for (int i=pos;i<pos+len;i++)
        Sub.ch[i-pos+1]=S.ch[i];
    Sub.length = len;
    return true;
}
//比较串的大小
int StrCompare(SString S,SString T){
    for(int i=1;i<=S.length&&i<=T.length;i++){
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    }
    return S.length-T.length;
}
//求串长
int StrLength(SString S){
    return S.length;
}

//定位操作
int Index(SString S,SString T){
    int i=1,n=StrLength(S),m=StrLength(T);
    SString sub;
    while(i<=n-m+1)
        {SubString(sub,S,i,m);
        if(StrCompare(sub,T)!=0)    ++i;
        else return i;}
    return 0;
}

//朴素模式匹配算法
int index(SString S,SString T){
    int i=1,j=1;
    while(i<=S.length&&j<=T.length)
    {
        if(S.ch[i]==T.ch[j]){
            i++,j++;
        }
        else{
            i=i-j+2;
            j=1;
        }
    }
    if(j>T.length)
        return i-T.length;
    else
        return 0;
}
