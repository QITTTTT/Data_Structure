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