#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

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
Status Value(Array A,ElemType &e,...){
    va_list ap;va_start(ap,e);int off;
    if(Locate(A,ap,off)<=0) return ERROR;
    e=*(A.base+off);
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
# define MAXSIZE 12500
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
    if(M.rhead) delete []M.rhead;
    if(M.chead) delete []M.chead;
    scanf("行数:%d,列数:%d,非零元个数:%d",&M.mu,&M.nu,&M.tu);
    M.rhead=(OLink*)calloc(M.mu+1,sizeof(OLink));
    if(!M.rhead)    exit(OVERFLOW);
    M.chead=(OLink*)calloc(M.nu+1,sizeof(OLink));
    if(!M.chead)    exit(OVERFLOW);
    int i,j,e,count=0;
    for(scanf("行号:%d,列号:%d,数据:%d",&i,&j,&e);i>0&&j>0&&count<M.tu;scanf("行号:%d,列号:%d,数据:%d",&i,&j,&e)){
        OLink p=(OLink)malloc(sizeof(OLNode));
        if(!p)  exit(OVERFLOW);
        p->i=i;p->j=j;p->e=e;
        //行插入
        if(!M.rhead[i]||M.rhead[i]->j>j){
            p->right=M.rhead[i];M.rhead[i]=p;
        }else{
            OLink q=M.rhead[i];
            while(!q->right&&q->right->j<j)   q=q->right;
            p->right=q->right;q->right=q;
        }
        //列插入
        if(!M.chead[i]||M.chead[i]->j>j){
            p->down=M.chead[i];M.chead[i]=p;
        }else{
            OLink q=M.chead[i];
            while(!q->down&&q->down->j<j)   q=q->down;
            p->down=q->down;q->down=q;
        }
        count++;
    }
    return OK;
}
