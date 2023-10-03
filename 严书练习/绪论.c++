#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include <limits.h>
//TODO:1.16
void read(){
    int x,y,z,temp;
    scanf("%d %d %d", &x, &y, &z);
    if(x<y){
        temp=x;
        x=y;
        y=temp;
    }
    if(y<z){
        temp=y;
        y=z;
        z=temp;
    }
    if(x<y){
        temp=x;
        x=y;
        y=temp;
    }
    printf("%d,%d,%d", x, y, z);
}

//TODO:1.17
int fabonacci(int k,int m){
    int n=0,a=m;
    if(m==k-1)   return 1;
    if(m<k-1)   return 0;
    while(m>a-k){
        n=n+fabonacci(k,--m);
    }
    return n;
}
//TODO:1.18
typedef enum{A,B,C,D,E} Schools;
typedef enum{female,male} Genders;
typedef enum{X,Y,Z} Events;
typedef struct{
    Schools schoolname;
    Genders gender;
    Events event;
    int score;
}Component;
typedef struct{
    int malesum;
    int femalesum;
    int scorenum;
}Sum;
Component components[100];
Sum sums[5];

//TODO:1.19
Status alg(int n,int a[]){
    int arrsize=7;
    if(n>arrsize)   return ERROR;
    for(int i=0;i<n;i++){
        if(i==0)  a[0]=1;
        else if(2*i*a[i-1]<=INT_MAX) a[i]=2*i*a[i-1];
        else return OVERFLOW;
    }
    return OK;
}
//TODO:1.20
void Polynomial(int a[],int n,int x){
    int sum=0;double last=a[0];
    sum+=a[0];
    for(int i=1;i<=n;i++){
        last=a[i]*last*x/a[i-1];
        sum+=last;
        
    }
    printf("%d",sum);
}
int main(){
    int a[4]={-1,4,-3,2};
    Polynomial(a,3,1);
}