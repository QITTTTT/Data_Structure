#include<stdio.h>
#include<stdlib.h>

typedef struct Linknode{
    int data;
    struct Linknode *next;
} *LiStack;