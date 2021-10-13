#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"jval.h"

void rand_function(Jval a[],int n);
void print(Jval a[],int n);
int int_compare(Jval *a,Jval *b);
int search(Jval a[],int l,int r,Jval *item,int (*compare)(Jval*,Jval*));
void swap(Jval a[],int i,int j);
void sort(Jval a[],int l,int r,size_t size,int (*compare)(Jval*,Jval*));

int main()
{
    int n=10;
    Jval *arr=(Jval*)malloc(sizeof(Jval)*n);
    rand_function(arr,n);
    print(arr,n);
    sort(arr,0,n-1,sizeof(Jval),int_compare);
    print(arr,n);
    return 0;
}

void rand_function(Jval a[],int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
        a[i]=new_jval_i(rand()%10+1);
}

void print(Jval a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i].i);
    printf("\n");
}

int int_compare(Jval *a,Jval *b)
{
    Jval *m,*n;
    m=a,n=b;
    if(m->i==n->i)
        return 0;
    return m->i>n->i ? 1:-1;
}

int search(Jval a[],int l,int r,Jval *item,int (*compare)(Jval*,Jval*))
{
    int i,res;
    if(r<=l)
        return -1;
    i=(r+l)/2;
    res=compare(item,&a[i]);
    if(res==0)
        return i;
    else if(res<0)
        return search(a,l,i-1,item,compare);
    else
        return search(a,i+1,r,item,compare);
}

void swap(Jval a[],int i,int j)
{
    Jval temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

void sort(Jval a[],int l,int r,size_t size,int (*compare)(Jval*,Jval*))
{
    if(r<=l)
        return;
    int i=l-1,j=r;
    int p=l-1,q=r;
    while(1)
    {
        while(compare(&a[++i],&a[r])<0);
        while(compare(&a[--j],&a[r])>0)
            if(j==l)
                break;
        if(i>=j)
            break;
        swap(a,i,j);
        if(compare(&a[i],&a[r])==0)
            swap(a,++p,i);
        if(compare(&a[j],&a[r])==0)
            swap(a,--q,j);
    }
    swap(a,i,r);
    j=i-1;
    i=i+1;
    int k;
    for(k=l;k<=p;k++)
        swap(a,k,j--);
    for(k=r-1;k>=q;k--)
        swap(a,k,i++);
    sort(a,l,j,size,compare);
    sort(a,i,r,size,compare);
}
