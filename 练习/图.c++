#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
#define VertexType char
typedef struct{
    char Vex[MaxVertexNum];
    int Edge[MaxVertexNum][MaxVertexNum];/*可以用bool型，内存占用更小*/
    int vexnum,arcnum;
}MGraph;
//边/弧
typedef struct ArcNode{
    int adjvex;            //边指向哪个结点
    struct ArcNode *next;  //指向下一条弧的指针
    //InfoType info;        //边权值
}ArcNode;

//顶点
typedef struct VNode{
    VertexType data;    //顶点信息
    ArcNode *first;     //第一条边
}VNode,AdjList[MaxVertexNum];

//用邻接表存储的图
typedef struct{
    AdjList vertices;
	int vexnum,arcnum;
}ALGraph;

//TODO:201.4
void Convert(ALGraph G,int a[][10]){
    for(int i=0;i<MaxVertexNum;i++){
        ArcNode* p=G.vertices[i].first;
        while(p!=nullptr){
            a[i][p->adjvex]=1;
            p=p->next;
        }
    }
}
