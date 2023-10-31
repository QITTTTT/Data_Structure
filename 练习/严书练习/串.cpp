#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>
#include <string.h>
#include <cstring>

//TODO:串的定长顺序存储表示
#define MAXSIZE 255
typedef unsigned char SString[MAXSIZE+1];//0号单元存放串的长度
//TODO:串的堆分配存储表示
typedef struct{
    char *ch;
    int length;
}HString;
//TODO:串的块链结构
#define CHUNKSIZE 2
typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;
typedef struct{
    Chunk *head,*tail;
    int curlen;
}LString;
//打印LString
void printLString(LString str) {
    Chunk *currentChunk = str.head;
    
    while (currentChunk != NULL) {
        for (int i = 0; i < CHUNKSIZE && currentChunk->ch[i] != '\0'; i++) {
            printf("%c", currentChunk->ch[i]);
        }
        currentChunk = currentChunk->next;
    }
    printf("\n");
}
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
//TODO:4.22
//插入到第n个字符之后
void Insert(LString &t,LString s,int n){
    //若n不合法或n=t.curlen，将s插到t的末尾,
    if(n<0||n>=t.curlen){
        Chunk*p=t.tail;Chunk*q=s.head;
        while(q){
            Chunk*r=new Chunk;*r=*q;
            r->next=p->next;p->next=r;p=r;
            q=q->next;
        }
        t.tail=p;
    }else if(n==0){
            Chunk*head=new Chunk;*head=*s.head;head->next=NULL;
            Chunk*p=s.head->next;Chunk*q=head;
            while(p){
                Chunk*r=new Chunk;*r=*p;
                r->next=q->next;q->next=r;q=r;
                p=p->next;
            }
            q->next=t.head;t.head=head;
        }else{
            Chunk*p=t.head;Chunk*q=p;
            while(n>0&&n>=CHUNKSIZE){
                if(p->ch[CHUNKSIZE-1]!='\0'){
                    n-=CHUNKSIZE;q=p;p=p->next;
                }else{
                    int i=0;
                    while(p->ch[i]!='\0'){i++;}
                    n-=i;q=p;p=p->next;
                }
            }
            Chunk*head=new Chunk;*head=*s.head;head->next=NULL;
                Chunk*r=s.head->next;Chunk*l=head;
                while(r){
                    Chunk*temp=new Chunk;*temp=*r;
                    temp->next=l->next;l->next=temp;l=temp;
                    r=r->next;
                }
            if(n==0){
                q->next=head;l->next=p;
            }else{
                int i=0;
                while(n>0){
                    if(p->ch[i]!='\0')  n--;
                    if(n!=0){
                        if(p->ch[i+1]=='\0'){
                            p=p->next;i=0;
                        }else{i++;}
                    }
                }
                Chunk*p1=new Chunk;
                int k=i+1;int j=0;
                while(p->ch[k]!='\0'){
                    p1->ch[j]=p->ch[k];
                    p->ch[k]='\0';k=k+1;j=j+1;
                }
                while(j<CHUNKSIZE){
                    p1->ch[j]='\0';
                }
                p1->next=p->next;p->next=p1;
                l->next=p1;p->next=head;
            }
        }
    t.curlen+=s.curlen;
}
//TODO:4.23
bool LStringSymmetry(LString S){
    struct Stack{
        char *base;
        int top;
    }SS;
    SS.base=new char[S.curlen];SS.top=0;
    int i;
    while(SS.top<S.curlen/2){
        for(i=0;i<CHUNKSIZE&&S.head->ch[i]!='\0'&&SS.top<S.curlen/2;i++){
            SS.base[SS.top++]=S.head->ch[i];
        }
        if(SS.top<S.curlen/2)    S.head=S.head->next;
    }
    int j;
    if(S.curlen%2==0){
        if(S.head->ch[i]!='\0')   j=i;
        else{S.head=S.head->next;j=0;}
    }else{
        if(S.head->ch[i]!='\0')    i=i;
        else{S.head=S.head->next;i=0;}
        if(S.head->ch[i+1]!='\0')    j=i+1;
        else{S.head=S.head->next;j=0;}
    }
    
    while(SS.top){
        for(;j<CHUNKSIZE&&S.head->ch[j]!='\0'&&SS.top;j++){
            if(SS.base[--SS.top]!=S.head->ch[j]){
                printf("不对称");return false;
            }
        }
        S.head=S.head->next;j=0;
    }
    printf("对称");return true;
}
//TODO:4.24
Status Concat(HString &T,HString S1,HString S2){
    if(T.ch)    delete(T.ch);
    T.ch=new char[S1.length+S2.length];
    if(!T.ch)   return OVERFLOW;
    int i;
    for(i=0;i<S1.length;i++){
        T.ch[i]=S1.ch[i];
    }
    while(i<S2.ch[i]){
        T.ch[i]=S2.ch[i];
        i++;
    }
    return OK;
}
//TODO:4.25
Status Replace(HString &S,HString T,HString V){
    if(S.length==0||V.length==0)    return INFEASIBLE;
    int si=0;
    while(si<S.length){
        int ti=0,sj=si;
        while(ti<T.length&&S.ch[sj]==T.ch[ti]){
            ti++;sj++;
        }
        if(ti==T.length){
            char*sp=S.ch;
            S.ch=new char[S.length-T.length+V.length];
            S.length=S.length-T.length+V.length;
            int sk=0;int vi=0;
            while(sk<si){ S.ch[sk]=sp[sk];sk++;}
            while(vi<V.length){ S.ch[sk]=V.ch[vi];sk++;vi++;}
            while(sk<S.length){ S.ch[sk]=sp[sj];sk++;sj++;}
            delete[] sp;
            si=si+V.length;
        }else   si++;
    }
    return OK;
}
//TODO:4.26
Status StrInsert(HString &S,int pos,HString T){
    if(pos<1||pos>S.length+1) return INFEASIBLE;
    char *sp=S.ch;
    S.ch=new char[S.length+T.length];S.length=S.length+T.length;
    int i=0;int ti=0;
    while(i<pos-1){ S.ch[i]=sp[i];i++;}
    while(ti<T.length){ S.ch[i]=T.ch[ti];i++;ti++;}
    while(i<S.length){ S.ch[i]=sp[pos-1];i++;pos++;}
    delete[] sp;
    return OK;
}//TODO:4.27
int Index(SString S,SString T,int pos){
    if(pos<1||pos>S[0]) return 0;
    int i=pos,j=1;
    while(i<=S[0]-T[0]+1){
        while(S[i]==T[j]&&S[i+T[0]-1]==T[T[0]]){
            i++;j++;
            while(S[i]==T[j]&&j<=T[0]){i++;j++;}
            if(j>T[0]) return i-T[0]+1;
        }i=i-j+2;j=1;
    }
    return 0;
}
//TODO:4.28
typedef struct StrNode{
    char chdata;
    StrNode *succ;  //下一个元素
    StrNode *next;  //next
}StrNode,*StrPtr;

Status Get_next(StrPtr &S){
    if(S==nullptr||S->succ==nullptr)    return ERROR;
    StrNode *q=S;
    StrNode *p=S->succ;p->next=q;
    while(p->succ){
        if(p->chdata==q->chdata||q==S){
            q=q->succ;p=p->succ;p->next=q;
        }else{q=q->next;}
    }
    return OK;
}

Status Get_nextval(StrPtr &S){
    if(S==nullptr||S->succ==nullptr)    return ERROR;
    StrNode *q=S;
    StrNode *p=S->succ;p->next=q;
    while(p->succ){
        if(p->chdata==q->chdata||q==S){
            q=q->succ;p=p->succ;
            if(q->chdata!=p->chdata)  p->next=q;
            else    p->next=q->next;
        }else{q=q->next;}
    }
    return OK;
}
//TODO:4.29
int Index_next(StrPtr S,StrPtr T,int pos){
    if(pos<1)   return ERROR;
    StrNode*sp=S,*tp=T;int counts=0;
    while(counts<pos&&sp->succ){
        sp=sp->succ;counts++;
    }
    if(counts!=pos)  return ERROR;
    int Tlength=0;
    while(tp->succ){
        Tlength++;tp=tp->succ;
    }
    tp=T->succ;
    while(sp&&tp){
        if(tp==T||sp->chdata==tp->chdata){
            sp=sp->succ;tp=tp->succ;counts++;
        }else{tp=tp->next;}
    }
    if(!tp){    return counts-Tlength;}
    else return 0;
}
//TODO:4.30
//TAG:补充滑动哈希
/*
1、动态规划:
    step1:dp[i][j]表示字符串前i个字符和前j个字符的最长公共后缀的长度
    step2:if(S[i]==S[j]) dp[i][j]=dp[i-1][j-1]+1;
          else  dp[i][j]=0;
    step3:用maxlength记录最大的dp[i][j],maxi记录对应的子串位置
    step4:先比较长度,再比较出现位置
2、哈希：
    会产生哈希冲突:可以构建两个哈希函数,也可测试不同的参数
*/
Status Find_DuplicateSubstring(SString S){
    //dp数组初始化
    int **dp=new int*[S[0]+1];
    for(int i=0;i<S[0]+1;i++){
        dp[i]=new int[S[0]+1];
        for(int j=0;j<S[0]+1;j++){
            dp[i][j]=0;
        }
    }
    //动态规划
    int maxlength=0;int maxi=0;
    for(int i=1;i<=S[0];i++){
        for(int j=1;j<=S[0];j++){
            if(S[i]==S[j]&&i!=j){
                dp[i][j]=dp[i-1][j-1]+1;
            }else   dp[i][j]=0;
            if(dp[i][j]>maxlength){
                maxlength=dp[i][j];maxi=i;
            }
        }
    }
    //返回子串
    if(maxlength!=0){
        SString T;
        T[0]=maxlength;
        for(int i=1;i<=T[0];i++){
            T[i]=S[maxi-maxlength+i];printf("%c",T[i]);
        }
        printf("第一次出现的位置为%d",maxi-maxlength+1);
    }
    return OK;
}
//TODO:4.31
/*
同样为动态规划
*/
Status LongestCommonSubstring(SString S,SString T){
    int **dp=new int*[S[0]+1];
    for(int i=0;i<S[0]+1;i++){
        dp[i]=new int[S[0]+1];
        for(int j=0;j<S[0]+1;j++){
            dp[i][j]=0;
        }
    }
    //动态规划
    int maxlength=0;int maxi=0;
    for(int i=1;i<=S[0];i++){
        for(int j=1;j<=T[0];j++){
            if(S[i]==T[j]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else   dp[i][j]=0;
            if(dp[i][j]>maxlength){
                maxlength=dp[i][j];maxi=i;
            }
        }
    }
    //返回子串
    if(maxlength!=0){
        SString U;
        U[0]=maxlength;
        for(int i=1;i<=U[0];i++){
            U[i]=S[maxi-maxlength+i];printf("%c",U[i]);
        }
        printf("第一次出现的位置为%d",maxi-maxlength+1);
    }
    return OK;
}