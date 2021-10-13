#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_function(int a[],int n);
void print(int a[],int n);
int int_compare(void const *x,void const *y);
int search(void *buf,int size,int l,int r,void *item,int int_compare(void const*x,void const*y));

int main()
{
    int res,n=10;
    int *arr=(int*)malloc(sizeof(int)*n);
    rand_function(arr,n);
    qsort(arr,n,sizeof(int),int_compare);
    int item=8;
    printf("Item need to find is: %d\n",item);
    printf("Array after sorting:\n");
    print(arr,n);
    res=search(arr,sizeof(int),0,n-1,&item,int_compare);
    printf("The value of res is: %d\n",res);
    return 0;
}

void rand_function(int a[],int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
        a[i]=rand()%10+1;
}

void print(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
    printf("\n");
}

int int_compare(void const *x,void const *y)
{
    int m,n;
    m=*((int*)x);
    n=*((int*)y);
    if(m==n)
        return 0;
    return m>n ? 1:-1;
}

int search(void *buf,int size,int l,int r,void *item,int int_compare(void const *x,void const *y))
{
    int i,res;
    if(r<l)
        return -1;
    i=(r+l)/2;
    res=int_compare(item,(char*)buf+(size*i));
    if(res==0)
        return i;
    else if(res<0)
        return search(buf,size,l,i-1,item,int_compare);
    else
        return search(buf,size,i+1,r,item,int_compare);
}