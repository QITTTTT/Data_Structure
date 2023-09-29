#include<stdio.h>
#include<stdlib.h>
//TODO:324/02
void swap(int &a,int &b){
        int temp=a;
        a=b;
        b=temp;
}

void BubbleSort(int(&nums)[],int n){
    bool flag=false;
        int low=0,high=n-1;
        while(low<high&&flag==false){
            flag=true;
            for(int i=low;i<high;i++)
                if(nums[i]>nums[i+1]){
                    swap(nums[i],nums[i+1]);
                    flag=false;
                }
            high--;
            for(int i=high;i>low;i--){
                if(nums[i]<nums[i-1]){
                    swap(nums[i],nums[i-1]);
                    flag=false;
                }
            }
            low++;

        }
}
//TODO:324/03
void Sort(int A[],int n){
    int low=0;int high=n-1;
    while(low<high){
        while(A[low]%2==1)  low++;
        while(A[high]%2==0) high--;
        if(low<high)    swap(A[low],A[high]);
    } 
}

//TODO:324/04:leetcode

//TODO:324/05:leetcode

//TODO:344/06 荷兰国旗问题

//TODO:335/04
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode,*LinkList;

void SelectSort(LinkList &L){
    LNode *p=L,*q=L->next,*r=L,*s=nullptr,*m=nullptr;
    while(r->next!=nullptr){
        int min=q->data;
        s=p;
        while(q){
            if(min>q->data){
                min=q->data;
                s=p;
            }
            q=q->next;
            p=p->next;

        }
        m=s->next;
        s->next=m->next;
        m->next=r->next;
        r->next=m;
        r=m;q=r->next;
    }
}
//TODO:335/05
bool IsMinHeap(int A[],int len){
    for(int i=len/2;i>=1;i--){
        if(2*i<=len){
            if(A[i]>A[2*i])  return false;
        }
        if(2*i+1<=len){
            if(A[i]>A[2*i+1])   return false;
        }
    }
    return true;
}
//TODO:349/02
void Merge(int *A,int m,int n){
    int B[m+n+1];
    for(int i=0;i<=m+n;i++)  B[i]=A[i];
    int i,j,k;
    for(i=1,j=m+1,k=1;i<=m&&j<=m+n&&k<=m+n+1;k++){
        if(B[i]<B[j]){
            A[k]=B[i];
            i++;
        }else{
            A[k]=B[j];
            j++;
        }
    }
    while(i<=m) A[k++]=B[i++];
    while(j<=m+n)   A[k++]=B[j++]; 
}

//TODO:350/03
int* Countsorting(int A[],int n){
    int B[n];
    for(int i=0;i<n;i++){
        int count=0;
        for(int j=0;j<n;j++){
            if(A[j]<A[i])   count++;
        }
        B[count]=A[i];
    }
    return B;
}
//TODO:350/04
void Sort(int *A,int n){
    A[0]=A[n];
    int low=1,high=n;
    while(low<high){
        while(low<high&&A[low]<=A[0]) low++;
        A[high]=A[low];
        while(low<high&&A[high]<=A[0])    high--;
        A[low]=A[high];
    }
    A[low]=A[0];
}