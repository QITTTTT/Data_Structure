#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>

//TODO:图的数组(邻接矩阵)存储表示
#define INFINITY INT_MAX    //最大值无穷
#define MAX_VERTEX_NUM 20   //最大顶点个数
typedef int VRType;
typedef char VertexType;
typedef int InfoType;
typedef enum {DG,DN,UDG,UDN}GraphKind;  //{有向图，有向网，无向图，无向网}
typedef struct  ArcCell{
    VRType adj;     //VRType是顶点关系类型。对无权图用1或0
                    //表示相邻否；对带权图，则为权值类型
    InfoType *info;     //
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct MGraph{
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs;                     //邻接矩阵
    int vexnum,arcnum;                  //图的当前顶点数和弧数
    GraphKind kind;                     //图的种类标志
}MGraph;
//TODO:图的邻接表存储表示
typedef struct ArcNode{
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
    InfoType *info;             //该弧相关信息的指针
}ArcNode;
typedef struct VNode{
    VertexType data;    //顶点信息
    ArcNode *firstarc;  //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertives;
    int vexnum,arcnum;      //图的当前顶点数和弧数
    GraphKind kind;               //图的种类标志
}ALGraph;
//TODO:7.14
Status CreateALGraphDG(ALGraph &G){
    G.kind=DG;
    printf("输入图的顶点数:");scanf("%d",&G.vexnum);
    printf("输入图的弧数:");scanf("%d",&G.arcnum);
    for(int i=0;i<G.vexnum;i++){
        printf("输入第%d个顶点的信息:",i+1);
        while ((getchar()) != '\n');
        scanf("%c",&G.vertives[i].data);
        G.vertives[i].firstarc=nullptr;
    }
    for(int i=0;i<G.arcnum;i++){
        printf("输入第%d条弧的信息:",i+1);
        char adjhead='\0',adjtail='\0';int info=0;
        printf("弧尾:");
        while ((getchar()) != '\n');
        scanf("%c",&adjtail);
        printf("弧头:");
        while ((getchar()) != '\n');
        scanf("%c",&adjhead);
        printf("弧相关的信息:");
        while ((getchar()) != '\n');
        scanf("%d",&info);
        ArcNode*p=(ArcNode*)malloc(sizeof(ArcNode));
        int k=0;while(G.vertives[k].data!=adjhead&&k<G.vexnum)  k++;
        if(k==G.vexnum) {printf("不存在结点");return ERROR;}
        *p={k+1,nullptr,&info};
        int j=0;
        while(G.vertives[j].data!=adjtail&&j<G.vexnum)   j++;
        if(j==G.vexnum) {printf("不存在结点");return ERROR;}
        p->nextarc=G.vertives[j].firstarc;G.vertives[j].firstarc=p;
    }
    return OK;
}
//TODO:7.15 邻接矩阵存储结构上实现图的基本操作
int LocateVex(MGraph G,VertexType u){
    for(int i=0;i<G.vexnum;i++){
        if(G.vexs[i]==u)    return i;
    }
    return -1;
}

Status InsertVex(MGraph &G,VertexType v){
    if(LocateVex(G,v)!=-1){
        printf("已有结点");
        return ERROR;
    }else{
        if(G.vexnum==MAX_VERTEX_NUM)    return OVERFLOW;
        else{
            int loc=0;
            while(G.vexs[loc]!='\0')    loc++;
            G.vexs[loc]=v;G.vexnum++;
            //初始化邻接矩阵
            for(int i=0;i<G.vexnum;i++){
                G.arcs[i][loc]={0,nullptr};
                G.arcs[loc][i]={0,nullptr};
            }
            return OK;
        }
    }
}

Status DeleteVex(MGraph &G,VertexType v){
    int loc=LocateVex(G,v);
    if(loc!=-1){
        G.vexs[loc]='\0';
        for(int i=0;i<G.vexnum;i++){
                G.arcs[i][loc]={0,nullptr};
                G.arcs[loc][i]={0,nullptr};
            }
        return OK;
    }
    return ERROR;
}

Status InsertArc(MGraph &G,VertexType v,VertexType w){
    int loc1=LocateVex(G,v);int loc2=LocateVex(G,w);
    if(loc1==-1||loc2==-1)  return ERROR;
    G.arcs[loc1][loc2]={1,nullptr};
    return OK;
}

Status DeleteArc(MGraph &G,VertexType v,VertexType w){
    int loc1=LocateVex(G,v);int loc2=LocateVex(G,w);
    if(loc1==-1||loc2==-1)  return ERROR;
    G.arcs[loc1][loc2].adj=0;
    return OK;
}
