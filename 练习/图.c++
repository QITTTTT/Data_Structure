#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
typedef struct{
    char Vex[MaxVertexNum];
    int Edge[MaxVertexNum][MaxVertexNum];/*可以用bool型，内存占用更小*/
    int vexnum,arcnum;
}MGraph;