#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"jval.h"

void create_array(Jval a[],int n);
void print_array(Jval a[],int n);
int jval_compare(Jval *a,Jval *b);
int jval_search(Jval a[],int l,int r,Jval *item,int (*compare)(Jval*,Jval*));
void swap_jval(Jval a[],int i,int j);
void jval_sort(Jval a[],int l,int r,int (*compare)(Jval*,Jval*));

int main()
{
    int n=10;
    Jval *arr=(Jval*)malloc(sizeof(Jval)*n);
    create_array(arr,n);
    printf("Array before sorting:\n");
    print_array(arr,n);
    jval_sort(arr,0,n-1,jval_compare);
    printf("Array after sorting:\n");
    print_array(arr,n);
    Jval item=new_jval_i(8);
    printf("Item is: %d\n",jval_i(item));
    int res=jval_search(arr,0,n-1,&item,jval_compare);
    printf("The index of item %d in array is: %d\n",jval_i(item),res);
    return 0;
}

void create_array(Jval a[],int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
        a[i]=new_jval_i(rand()%10+1);
}

void print_array(Jval a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",jval_i(a[i]));
    printf("\n");
}

int jval_compare(Jval *a,Jval *b)
{
    Jval m,n;
    m=*a;
    n=*b;
    if(m.i==n.i)
        return 0;
    return m.i>n.i ? 1:-1;
}

int jval_search(Jval a[],int l,int r,Jval *item,int (*compare)(Jval*,Jval*))
{
    if(r<l)
        return -1;
    int i,res;
    i=(r+l)/2;
    res=compare(item,&a[i]);
    if(res==0)
        return i;
    else if(i<0)
        return jval_search(a,l,i-1,item,compare);
    else 
        return jval_search(a,i+1,r,item,compare);
}

void swap_jval(Jval a[],int i,int j)
{
    Jval temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

void jval_sort(Jval a[],int l,int r,int (*compare)(Jval*,Jval*))
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
        swap_jval(a,i,j);
        if(compare(&a[i],&a[r])==0)
            swap_jval(a,i,++p);
        if(compare(&a[j],&a[r])==0)     
            swap_jval(a,j,--q);
    }
    swap_jval(a,i,r);
    j=i-1;
    i=i+1;
    int k;
    for(k=l;k<=p;k++)
        swap_jval(a,k,j--);
    for(k=r-1;k>=q;k--)
        swap_jval(a,k,i++);
    jval_sort(a,l,j,compare);
    jval_sort(a,i,r,compare);
}