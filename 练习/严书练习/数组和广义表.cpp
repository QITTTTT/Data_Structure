#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>
//TODO:串的定长顺序存储表示
#define MAXSIZE 255
typedef unsigned char SString[MAXSIZE+1];//0号单元存放串的长度
//TODO:数组的顺序存储表示和实现
//-------------------------数组的顺序存储表示---------------------------
#include <stdarg.h>
#define MAX_ARRAY_DIM 8     //数组最大维度
typedef int ElemType;
typedef struct{
    ElemType *base;
    int dim;
    int *bounds;    //各维度的长度
    int *constants; //数组映像函数常量基址
}Array;
//--------------------------基本操作------------------------------------
Status InitArray(Array &A,int dim,...){
    if(dim<1||dim>MAX_ARRAY_DIM)    return ERROR;
    A.dim=dim;
    A.bounds=new int[dim];
    if(!A.bounds)   exit(OVERFLOW);
    va_list ap;va_start(ap,dim);int elemtotal=1;
    for(int i=0;i<dim;i++){
        A.bounds[i]=va_arg(ap,int);
        if(A.bounds[i]<0)   return UNDERFLOW;
        elemtotal*=A.bounds[i];
    }
    va_end(ap);
    A.base=new ElemType[elemtotal];
    if(!A.base) exit(OVERFLOW);
    A.constants=new int[dim];
    if(!A.constants)    exit(OVERFLOW);
    A.constants[dim-1]=1;   //指针的增减以元素的大小为单位
    for(int i=dim-2;i>=0;i--){
        A.constants[i]=A.bounds[i+1]*A.constants[i+1];
    }
    return OK;
}

Status DestroyArray(Array &A){
    if(!A.base) return ERROR;
    delete []A.base;A.base=nullptr;
    if(!A.bounds)   return ERROR;
    delete []A.bounds;A.bounds=nullptr;
    if(!A.constants)    return ERROR;
    delete []A.constants;A.constants=nullptr;
    return OK;
}

Status Locate(Array A,va_list ap,int &off){
    off=0;
    for(int i=0;i<A.dim;i++){
        int ind=va_arg(ap,int);
        if(ind<0||ind>=A.bounds[i]-1)
        off+=A.constants[i]*ind;
    }
    return OK;
}
//读取元素
Status Value(Array A,ElemType *e,...){
    va_list ap;va_start(ap,e);int off;
    if(Locate(A,ap,off)<=0) return ERROR;
    *e=*(A.base+off);
    return OK; 
}
//修改元素
Status Assign(Array &A,ElemType e,...){
    va_list ap;va_start(ap,e);int off;
    if(Locate(A,ap,off)<=0) return ERROR;
    *(A.base+off)=e;
    return OK;
}
//TODO:三元组顺序表
//-----------------------稀疏矩阵的三元组顺序表存储表示--------------------
typedef struct{
    int i,j;
    ElemType e;
}Triple;
typedef struct{
    Triple  data[MAXSIZE+1];
    int mu,nu,tu;
}TSMatrix;
//-----------------------------------------------------------------------
//转置算法
Status TransposeSMatrix(TSMatrix M,TSMatrix &T){
    T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
    if(T.tu!=0){
        int q=1;
        for(int col=1;col<=M.nu;col++){
            for(int p=1;p<=M.tu;p++){
                if(M.data[p].j==col){
                    T.data[q].i=col;
                    T.data[q].e=M.data[p].e;
                    T.data[q].j=M.data[p].i;
                    q++;
                }
            }
        }
    }
    return OK;
}
//快速转置
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T){
    T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
    if(T.tu){
        int *num=new int[M.nu+1];
        int *cpot=new int[M.nu+1];  //0元素不使用
        for(int i=1;i<=M.tu;i++){
            num[M.data[i].j]++;
        }
        cpot[1]=1;
        for(int i=2;i<=M.tu;i++){
            cpot[i]=cpot[i-1]+num[i-1];
        }
        for(int i=1;i<=M.tu;i++){
            T.data[cpot[M.data[i].j]].e=M.data[i].e;
            T.data[cpot[M.data[i].j]].i=M.data[i].j;
            T.data[cpot[M.data[i].j]].j=M.data[i].i;
            cpot[M.data[i].j]++;
        }
        delete []num;
        delete []cpot;
    }
    
    return OK;
}
//TODO:行逻辑链接的顺序表
//--------------------行逻辑链接------------------------
#define MAXRC 100
typedef struct{
    Triple data[MAXSIZE+1];
    int rpos[MAXRC+1];  //各行第一个非零元的位置表
    int mu,nu,tu;
}RLSMatrix;
//-----------------------------------------------------
//矩阵乘法
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q){
    if(M.tu!=N.mu)  return ERROR;
    Q.mu=M.mu;Q.nu=N.nu;Q.tu=0;
    if(M.tu*N.tu!=0){
        int *ctemp=new int[Q.nu+1];
        for(int arow=1;arow<=M.mu;arow++){
            for(int i=1;i<=Q.nu;i++)    ctemp[i]=0;     //累加器清零
            Q.rpos[arow]=Q.nu+1;
            int mp;      //控制循环次数
            if(arow<M.mu)   mp=M.rpos[arow+1];
            else mp=M.tu+1;
            for(int p=M.rpos[arow];p<mp;p++){
                int np;int nrow=M.data[p].j;
                if(nrow<N.mu)    np=N.rpos[nrow+1];
                else np=N.tu+1;
                for(int q=N.rpos[nrow];q<np;q++){
                    ctemp[N.data[q].j]+=N.data[q].e*M.data[p].e;
                }
            }
            for(int i=1;i<Q.nu;i++){
                if(ctemp[i]){
                    Q.tu++;
                    if(Q.tu>MAXSIZE)    return ERROR;
                    Q.data[Q.tu]={arow,i,ctemp[i]};
                }
            }
        }
        delete []ctemp;
    }
    return OK;
}
//TODO:十字链表
//-------------------稀疏矩阵的十字链表存储表示---------------
typedef struct OLNode{
    int i,j;
    ElemType e;
    OLNode*right,*down;
}*OLink;
struct CrossList{
    OLink *rhead, *chead;
    int mu,nu,tu;
};

//Create
Status CreateSMatrix_OL(CrossList &M){
    if(M.rhead) free(M.rhead);
    if(M.chead) free(M.chead);
    printf("输入矩阵的行号列号非零元个数\n");
    scanf("%d,%d,%d",&M.mu,&M.nu,&M.tu);
    M.rhead=(OLink*)calloc(M.mu+1,sizeof(OLink));
    if(!M.rhead)    exit(OVERFLOW);
    M.chead=(OLink*)calloc(M.nu+1,sizeof(OLink));
    if(!M.chead)    exit(OVERFLOW);
    int i,j,e,count=0;
    printf("非零元信息\n");
    for(scanf("%d,%d,%d",&i,&j,&e);i>0&&j>0&&count<M.tu;){
        OLink p=(OLink)malloc(sizeof(OLNode));
        if(!p)  exit(OVERFLOW);
        p->i=i;p->j=j;p->e=e;
        //行插入
        if(!M.rhead[i]||M.rhead[i]->j>j){
            p->right=M.rhead[i];M.rhead[i]=p;
        }else{
            OLink q=M.rhead[i];
            while(q->right&&q->right->j<j)   q=q->right;
            p->right=q->right;q->right=p;
        }
        //列插入
        if(!M.chead[j]||M.chead[j]->i>i){
            p->down=M.chead[j];M.chead[j]=p;
        }else{
            OLink q=M.chead[j];
            while(q->down&&q->down->j<j)   q=q->down;
            p->down=q->down;q->down=p;
        }
        count++;
        if(count<M.tu)  scanf("%d,%d,%d",&i,&j,&e);
    }
    return OK;
}

//Addition
/*
逐行进行加法
    1.在进行节点操作时，因为会有删除和插入操作，所以需要记录两个前驱结点
    2.因为每次循环中行数是固定的，所以行前驱结点pre只需设立一个;而列数不确定，所以需要建立一个指针数组hl来记录每列的前驱结点
    3.pre指向的是pa的行前驱结点,而hl用来指向列中处理完的最后一个结点;两者处理不同的原因是无法确定下一个p的列数，但可以确定行数。
        因此当插入行的第一个结点时，无法确定下一个p的列数大小，即不能更新pre，只有确定了pa->j<p->j时，才可更新pre;
*/
Status AdditionMatrix(CrossList &A,CrossList B){
    OLNode*pa=A.rhead[1],*pb=B.rhead[1],*pre=nullptr;   //pre指向pa的前驱结点
    OLink*hl=(OLink*)calloc(A.nu+1,sizeof(OLink));
    if(!hl) exit(OVERFLOW);
    for(int i=1;i<=A.nu;i++)    hl[i]=A.chead[i];
    for(int row=1;row<=A.mu;row++,pa=A.rhead[row],pb=B.rhead[row]){
        while(pb){
            //复制pb结点
            if(pa==nullptr||pa->j>pb->j){
                OLNode*p=(OLNode*)malloc(sizeof(OLNode));
                if(!p)  exit(OVERFLOW);
                *p=*pb;
                //处理行
                if(!pa){
                    A.rhead[row]=p;
                }else if(pre==nullptr){
                    A.rhead[row]=p;p->right=pa;
                }else{
                    pre->right=p;
                }p->right=pa;pre=p;
                //处理列
                if(!A.chead[p->j]||A.chead[p->j]->i>p->i){
                    p->down=A.chead[p->j];A.chead[p->j]=p;hl[p->j]=p;
                }else{
                    p->down=hl[p->j]->down;hl[p->j]->down=p;
                }hl[p->j]=p;
            }else if(pa->j<pb->j){
                pre=pa;pa=pa->right;
            }else if(pa->j==pa->j){
                pa->e+=pb->e;
                if(pa->e==0){
                    if(pre==nullptr){
                        A.rhead[row]=pa->right;
                    }else{
                        pre->right=pa->right;
                    }
                    if(A.chead[pa->j]==pa){
                        A.chead[pa->j]=pa->down;
                    }else{
                        hl[pa->j]->down=pa->down;
                    }free(pa);

                }
                
            }
            pb=pb->right;
        }
    }
    return OK;
}
void PrintMatrix(CrossList M) {
    for (int i = 1; i <= M.mu; i++) {
        OLink p = M.rhead[i];
        for (int j = 1; j <= M.nu; j++) {
            if (p && p->j == j) {
                // 使用 printf 输出稀疏矩阵元素
                printf("%d ", p->e);
                p = p->right;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
//TODO:广义表的存储结构
//----------------------------广义表的头尾链表存储结构--------------------------------------
typedef enum{ATOM,LIST} ElemTag;    //ATOM==0:原子,LIST==2:子表
#define AtomType int
typedef struct GHTLNode{
    ElemTag tag;
    union{
        AtomType atom;
        struct{GHTLNode*hp,*tp;}ptr;
    };
}*GHTList;
//---------------------------广义表的扩展线性链表存储表示------------------------------------
typedef struct GLLNode{
    ElemTag tag;
    union{
        AtomType atom;
        struct GLLNode *hp;
    };
    GLLNode *tp;    //相当于next
}*GLList;
//--------------------------m元多项式的广义表的存储结构------------------------------
typedef struct MPNode{
    ElemTag tag;
    int exp;
    union{
        float   coef;   //系数域
        MPNode *hp;
    };
    MPNode *tp;
}*MPList;
//TODO:广义表的递归算法
//---------------------------------求广义表的深度--------------------------------------
/*
基本项：DEPTH(LS)=1  LS为空表
       DEPTH(LS)=0  LS为原子
归纳项：DEPTH(LS)=1+MAX{DEPTH(a<i>)} 
*/
int GHTListDepth(GHTList L){
    if(!L)  return 1;
    if(L->tag==0)   return 0;
    GHTList p=nullptr;int max;
    for(max=0,p=L;p;p=p->ptr.tp){
        int d=GHTListDepth(p->ptr.hp);
        if(max<d)   max=d;
    }
    return max+1;
}
//--------------------------------复制广义表------------------------------------------------
/*
基本项:置空表,当LS为空表;
归纳项:1.复制表头;2.复制表尾
*/
Status CopyGHTList(GHTList &T,GHTList L){
    if(!L)  T=nullptr;
    else{
        T=(GHTList)malloc(sizeof(GHTLNode));
        if(!T)  exit(OVERFLOW);
        T->tag=L->tag;
        if(T->tag==0){
            T->atom=L->atom;
        }else{
            CopyGHTList(T->ptr.hp,L->ptr.hp);
            CopyGHTList(T->ptr.tp,L->ptr.tp);
        }
    }
    return OK;
}
//-----------------------------------建立广义表--------------------------------
/*
基本项：置空广义表  当S为空表串时
        建原子节点的子表    当S为单字符串时
归纳项：假设sub为脱去S最外层括弧的子串，记为's1,s2,...,sn'，其中si的为非空字符串。对每一个si建立一个表结点，
        并令其hp域的指针为由si建立的子表的头指针，除最后建立的表结点的尾指针为NULL外，其余表结点的尾指针均指向在它之后建立的表结点。

循环加递归
*/
Status StrAssign(SString &S,char chars[]){
    int i=0;
    while(chars[i]){
        S[i+1]=chars[i];
        i++;
    }
    S[0]=i;
    return OK;
}
Status StrCompare(SString S,SString T){
    if(S[0]==T[0]){
        for(int i=1;i<=S[0];i++){
            if(S[i]>T[i])   return 1;
            if(S[i]<T[i])   return -1; 
        }
    }
    return S[0]-T[0];
}
Status SubString(SString &sub,SString S,int pos,int len){
    if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)  return ERROR;
    sub[0]=len;
    for(int i=pos,k=1;i<pos+len;i++,k++){
        sub[k]=S[i];
    }
    return OK;
}
Status StrCopy(SString &T,SString S){
    T[0]=S[0];
    int i=1;
    while(i<=T[0]){
        T[i]=S[i];i++;
    }
    return OK;
}
Status ClearString(SString &S){
    S[0]=0;
    return OK;
}
Status sever(SString &str,SString &hstr){
    int n=str[0];int i=0,k=0;
    do{
        i++;
        if(str[i]=='(') ++k;
        else if(str[i]==')')    --k;
    }while(i<n&&(str[i]!=','||k!=0));
    if(i<n){
        SubString(hstr,str,1,i-1);SubString(str,str,i+1,n-i);
    }else{StrCopy(hstr,str);ClearString(str);}
    return OK;
}
Status CreateGHTList(GHTList &L,SString S){
    SString emp;char chars[]="()";StrAssign(emp,chars);
    if(StrCompare(S,emp)==0)    L=nullptr;
    else{
        L=(GHTList)malloc(sizeof(GHTLNode));
        if(!L)  exit(OVERFLOW);
        if(S[0]==1){
            L->tag=ATOM;
            L->atom=S[1];
            printf("%c",L->atom);
        }else{
            L->tag=LIST;GHTList p=L,q=nullptr;
            SString sub;
            SubString(sub,S,2,S[0]-2);
            
            do{
                
                SString hsub;sever(sub,hsub);
                CreateGHTList(p->ptr.hp,hsub);q=p;
                if(sub[0]!=0){
                    p=(GHTList)malloc(sizeof(GHTLNode));
                    if(!p)  exit(OVERFLOW);
                    p->tag=LIST;q->ptr.tp=p;
                }
            }while(sub[0]!=0);
            q->ptr.tp=nullptr;
        }
    }
    return OK;
}
void PrintGHTList(GHTList L) {
    if (L==nullptr) {
        printf("()");
        return;
    }
    if (L->tag==ATOM) {
        printf("%c", L->atom);
    } else if (L->tag==LIST) {
        printf("(");
        if (L->ptr.hp) {
            PrintGHTList(L->ptr.hp);  // 打印头部
        }
        GHTList p = L->ptr.tp;  // 开始处理尾部
        while(p){
            printf(", ");
            PrintGHTList(p->ptr.hp);  // 打印头部
            p = p->ptr.tp;  // 移动到下一个节点
        }
        printf(")");
    }
}

//TODO:5.18
/*
逆置：
    1：我们把数组分成两个整体：后k个和前n-k个
    2：经过移动，后k个元素会和前n-k个元素进行位置调换。
    所以我们可以先整体进行逆置，再分别对两堆元素进行逆置。
*/
Status Reverse(int A[],int start,int end){
    if(start>end)   return ERROR;
    int e;
    while(start<end){
        e=A[start];
        A[start++]=A[end];
        A[end--]=e;
    }
    return OK;
}
Status Move_1(int A[],int len,int k){
    k=k%len;
    Reverse(A,0,len-1);
    Reverse(A,0,k-1);
    Reverse(A,k,len-1);
    return OK;
}
/*
哈希思想：
    坐标为i的元素，应移动到j=(i+k)%n上，i=j-k+n;环的数量为最大公约数；
*/
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
Status Move_2(int A[],int len,int k){
    k=k%len;int kl=gcd(len,k);
    for(int count =0;count<kl;count++){
        int i=count;int j=(i+k)%len;int e=A[j];int ecount=(j+k)%len;
        do{
            A[j]=A[i];
            j=i;
            if(j-k>=0)   i=j-k;
            else i=j-k+len;
        }while(j!=ecount);
        A[j]=e;
    }
    return OK;
}
//TODO:5.19
/*
思想：
    建立一个二维数组，记录行的最小值元素，列的最大值元素。
    第一遍遍历矩阵，得到二维数组；第二遍遍历矩阵，判断其对应的值是否满足马鞍点的要求
    如果是则输出；不是则继续扫描。
*/
Status Saddle_point(int **A,int m,int n){
    int *a=new int[m];int *b=new int[n];    //a记录行最小元素，b记录列最大元素
    //初始化数组
    for(int i=0;i<m;i++){
        a[i]=INT_MAX;
    }
    for(int i=0;i<n;i++){
        b[i]=INT_MIN;
    }
    //第一遍扫描矩阵，得到两个数组
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(A[i][j]<a[i])    a[i]=A[i][j];
            if(A[i][j]>b[j])    b[j]=A[i][j];
        }
    }
    //第二遍扫描矩阵，寻找马鞍点
    int tag=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(A[i][j]==a[i]&&A[i][j]==b[j]){
                tag=0;
                printf("行号:%d,列号:%d,元素值:%d",i+1,j+1,A[i][j]);
            }
        }
    }
    if(tag) printf("没有马鞍点");
    delete[] a;delete[] b;
    return OK;
}

//TODO:5.20
/*
不会处理变参，所以我直接用课本中的例子
*/
void Print(int **A,int m){  
    //m为最大次数
    for(int i=m;i>=0;i--){
        for(int j=i,k=0;j>=0;j--,k++){
            if(A[j][k]!=0){
                printf("%d",A[j][k]);
                if(j!=0)    printf("%cE%d",'x',j);
                if(k!=0)    printf("%cE%d",'y',k);
                if(i!=0)    printf("+");
            }
        }
    }
}
//TODO:5.21
Status Addition(TSMatrix &C,TSMatrix A,TSMatrix B){
    C.mu=A.mu;C.nu=A.nu;
    int ai=0,bi=0,ci=0;
    while(ai<A.nu||bi<B.nu){
        if(A.data[ai].i<B.data[bi].i){
            C.data[ci]=A.data[ai];
            ci++;ai++;
        }else if(A.data[ai].i==B.data[bi].i){
            if(A.data[ai].j<B.data[bi].j){
                C.data[ci]=A.data[ai];
                ci++;ai++;
            }else if(A.data[ai].j==B.data[bi].j){
                C.data[ci]=A.data[ai];C.data[ci].e+=B.data[bi].e;
                ai++;bi++;ci++;
            }else{
                C.data[ci]=B.data[bi];
                ci++;bi++;
            }
        }else{
            C.data[ci]=B.data[bi];
            ci++;bi++;
        }
    }//while
    C.tu=ci;
    return OK;
}
