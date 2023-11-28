#include<stdio.h>
#include<stdlib.h>
//TODO:2-路插入排序
void Two_Directions_Insert_sort(int nums[],int n){
    int *a=new int[n];
    a[0]=nums[0];int first=0,final=0;
    for(int i=1;i<n;i++){
        if(nums[i]<a[0]){
            if(first==0){       //第一个小于a[0]的数单独处理
                first=n-1;a[first]=nums[i];
            }else{
                int j=n-1;
                while(j>=first&&a[j]>nums[i])   j--;
                for(int k=first;k<=j;k++)   a[k-1]=a[k];
                a[j]=nums[i];first=j;
            }
        }else{
            int j=0;
            while(j<=final&&a[j]<nums[i])   j++;
            for(int k=final;k>=j;k--)   a[k+1]=a[k];
            a[j]=nums[i];final=j;
        }
    }
    for(int i=0;i<n;i++)  nums[i]=a[(first+i)%n];
    delete[] a;
}
void twoo_Insert_sort(int nums[],int n){
    int *a=new int[n];
    a[0]=nums[0];int first=0,final=0;
    for(int i=1;i<n;i++){
        if(nums[i]<a[first]){
            first = (first - 1 + n) % n;
            a[first] = nums[i];
        }else{
            final = (final + 1) % n;
            a[final] = nums[i];
        }
    }
    for(int i=0;i<n;i++)  nums[i]=a[(first+i)%n];
    delete[] a;
}
int main(){
    int nums[]={3,2,5,10,1,9};
    int n=6;
    for(int i=0;i<n;i++){
        printf("%d,",nums[i]);
    }
    printf("\n");
    two_Insert_sort(nums,n);
    for(int i=0;i<n;i++){
        printf("%d,",nums[i]);
    }
    return 0;
}