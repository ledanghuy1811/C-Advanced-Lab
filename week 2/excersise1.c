#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void create_array(int a[],int n);
void print_array(int a[],int n);
int int_compare(void const *x,void const *y);
int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*));

int main()
{
    int n=10;
    int *arr=(int*)malloc(sizeof(int)*n);
    create_array(arr,n);
    printf("Array after sorting:\n");
    qsort(arr,n,sizeof(int),int_compare);
    print_array(arr,n);
    int item=5;
    int res=gen_search(arr,sizeof(int),0,n-1,&item,int_compare);
    printf("The index of item %d is %d\n",item,res);
    return 0;
}

void create_array(int a[],int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
        a[i]=rand()%10+1;
}

void print_array(int a[],int n)
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

int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*))
{
    if(r<l)
        return -1;
    int mid,cmp;
    mid=(l+r)/2;
    cmp=compare(item,(char*)(buf+size*mid));
    if(cmp==0)
        return mid;
    else if(cmp<0)
        return gen_search(buf,size,l,mid-1,item,compare);
    else
        return gen_search(buf,size,mid+1,r,item,compare);
}