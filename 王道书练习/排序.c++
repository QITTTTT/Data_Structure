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
