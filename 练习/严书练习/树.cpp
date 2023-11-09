#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

//TODO:二叉树的链式存储
typedef int ElemType
typedef struct BiTNode{
    ElemType data;
    struct BiTNode*lchild,*rchild;
}BiTNode,*BiTree; 
//TODO: 遍历的非递归算法
//-----------------------------相关栈的定义及操作-------------------------

void visit(BiTNode* T){
    if(T!=nullptr)
    printf("%d",T->data);
}