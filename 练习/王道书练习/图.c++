#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
#define VertexType char
#define MaxSize 10

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

ArcNode* FirstNeighbor(ALGraph G,int v){
    return G.vertices[v].first;
}

ArcNode* NextNeighbor(ALGraph G,int v,ArcNode* w){
    return w->next;
}

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

//TODO:211.02

bool DFS(ALGraph G,int v,int& vertexnum,int& edgenum,bool (&visited)[]){
    vertexnum++;
    visited[v]=true;
    for(ArcNode* w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
			if(!visited[w->adjvex]){
                edgenum++;
   				DFS(G,w->adjvex,vertexnum,edgenum,visited);
			}
}



bool isTree(ALGraph G){
    bool visited[MaxVertexNum]={false};
    int vertexnum=0,edgenum=0;
    DFS(G,0,vertexnum,edgenum,visited);
    if(vertexnum==edgenum+1)
        return false;
    for(int i=0;i<MaxVertexNum;i++){
        if(visited[i]==false)
            return false;
    }
    return true;

}
int visit(ALGraph G,int v){
    printf("%c",G.vertices[v].data);
    return 0;
}
//TODO:211/03

typedef struct{
    int data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}

bool Push(SqStack &S,int x){
    if(S.top==MaxSize-1)
        return false;
    S.top=S.top+1;
    S.data[S.top]=x;
    return true;
}

bool Pop(SqStack &S,int &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top--];
    return true;
}

bool GetTop(SqStack S,int &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    return true;
}
bool IsEmpty(SqStack S){
    if(S.top==-1)
        return true;
    return false;
}

/*
void DFS_non_recursion(ALGraph G,int v){
    bool *visited=(bool*)malloc(G.vexnum*sizeof(bool));
    for(int i=0;i<G.vexnum;i++)
        visited[i]=false;
    SqStack S;
    InitStack(S);
    Push(S,v);visited[v]=true;
    while(!IsEmpty(S)){
        int k=0;
        Pop(S,k);
        visit(G,k);
        for(int w=FirstNeighbor(G,k)->adjvex;w>=0;w=NextNeighbor(G,k,w)->adjvex)
        {if(!visited[w]){
            Push(S,w);
            visited[w]=true;
        }}
    }

}
*/

//TODO:211/04
//TODO:深度优先遍历
/*
bool visited[MAX_VERTEX_NUM];
bool DFS(Graph G,int v,int m){
    bool my_bool=false;
    if(v==w)
        my_bool=true;
    visited[v]=TURE;
    for(w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
        if(!visited[w]){
            if(!my_bool)
                my_bool=DFS(G,w,m);
        }
    return my_bool;
}
*/

//TODO:广度优先遍历
/*
bool visited[MAX_VERTEX_NUM];
bool BFS(ALGraph G,int v,int m){
    bool my_bool=false;
    if(v==m) my_bool=true;
    visited[v]=true;
    InitQueue(Q);
    EnQueue(Q,v);
    while(!IsEmpty(Q)){
        DeQueue(Q,v);
        for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w)){
           if(!visited[w])
            {
                if(w==m) 
                    my_bool=true;
                visited[w]=true;
                EnQueue(Q,w);
            }
        }
    }
    return my_bool;
}
*/