#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
// 定义二叉树节点结构
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建新节点
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
        return root;
    }
}

// 中序遍历（左-根-右）
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
void Delete(TreeNode* &T)/*删除结点*/
{
    if(T){
        Delete(T->left);
        Delete(T->right);
        TreeNode*temp=T;
        T=nullptr;
        free(temp);
    }
}
void Search_x(TreeNode* T,int x)/*查找x值的结点并删除左右子树*/
{
    if(T)
    {
        if(T->data==x)
            {
                Delete(T->left);
                Delete(T->right);
            }
        else
        {Search_x(T->left,x);
        Search_x(T->right,x);}
    }
}

// TODO:实现栈的操作
typedef struct{
    TreeNode* node[MaxSize];
    int top;
}SqStack;

void InitSqStack(SqStack &S){
    S.top=-1;
}

bool Pop(SqStack &S,TreeNode* &s){
    if(S.top<0)
        return false;
    s=S.node[S.top--];
    return true;
}

bool Push(SqStack &S,TreeNode* s){
    if(S.top>=MaxSize)
        return false;
    S.node[++S.top]=s;
    return true;
}
bool GetTop(SqStack S,TreeNode* &x){
    if(S.top==-1)
        return false;
    x=S.node[S.top];
    return true;
}

//函数

bool PostOrder(TreeNode* T){
    if(T==nullptr)
        return false;
    SqStack S;
    InitSqStack(S);
    TreeNode* p = T,*r=nullptr;
    while(p!=nullptr||S.top>-1)
    {
        if(p!=nullptr)
        {
            Push(S,p);
            p=p->left;
            
        }else{
            GetTop(S,p);
            if(p->right!=nullptr&&p->right!=r)
                p=p->right;
            else{
                Pop(S,p);
                printf("%d ", p->data);
                r=p;
                p=nullptr;
            }
        }
    }
    return true;
}
void Search_x1(TreeNode* T,int x)/*查找x值并打印祖先*/
{
    SqStack S;
    InitSqStack(S);
    TreeNode*p=T;
    TreeNode*r=nullptr;
    while(p||S.top!=-1)
        if(p)
            {
                Push(S,p);
                p=p->left;
            }
        else
            {
                GetTop(S,p);
                if(p->right&&r!=p->right)
                    {
                        p=p->right;
                    }
                else
                    {
                        if(p->data==x)
                            {
                                Pop(S,p);
                                while(S.top!=-1)
                                    {
                                        printf("祖先元素的值为");
                                        Pop(S,p);
                                        printf("%d",p->data);
                                    }
                                p=nullptr;
                            }
                        else
                            {
                                Pop(S,p);
                                r=p;
                                p=nullptr;
                            }
                    }
            }
}
typedef struct{
    TreeNode*data[100];
    int front,rear;
}Queue;
int BiTWidth(TreeNode* T){
    int maxwidth=1;
    int width=1;
    TreeNode*p=nullptr;
    Queue Q;
    Q.front=Q.rear=-1;
    Q.data[++Q.rear]=T;
    int q=0;/*本层最后结点的序号*/
    while(Q.rear!=Q.front)
    {
        if(Q.front!=q)
        {
            p=Q.data[++Q.front];
            if(p->left)
                Q.data[++Q.rear]=p->left;
            if(p->right)
                Q.data[++Q.rear]=p->right;
        }
        else
        {
            width=Q.rear-q;
            q=Q.rear;
            if(maxwidth<width)
            maxwidth=width;    
                
        }
    }
    return maxwidth;
}
int main() {
    struct TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    root = insertNode(root, 3);
    root = insertNode(root, 7);

    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("后序遍历结果: ");
    PostOrder(root);
    printf("最大宽度是%d",BiTWidth(root));
    
    printf("\n");


    return 0;
}
