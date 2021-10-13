#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_function(int a[],int n);
void print(int a[],int n);
void exchange(void *buf,int size,int i,int j);
int int_compare(void const *x,void const *y);
void sort(void *a,int size,int l,int r,int (*compare)(void const*,void const*));

int main()
{
    int n=10;
    int *arr=(int*)malloc(sizeof(int)*n);
    rand_function(arr,n);
    print(arr,n);
    sort(arr,sizeof(int),0,n-1,int_compare);
    print(arr,n);
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

void exchange(void *buf,int size,int i,int j)
{
    char temp=*((char*)(buf+i*size));
    *((char*)(buf+i*size))=*((char*)(buf+j*size));
    *((char*)(buf+j*size))=temp;
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

void sort(void *a,int size,int l,int r,int (*compare)(void const*,void const*))
{
    if(r<=l)
        return;
    int i=l-1,j=r;
    int p=l-1,q=r;
    while(1)
    {
        while(compare((char*)a+(++i)*size,(char*)a+r*size)<0);
        while(compare((char*)a+r*size,(char*)a+(--j)*size)<0)
            if(j==l)
                break;
        if(i>=j)
            break;
        exchange(a,size,i,j);
        if(compare((char*)a+i*size,(char*)a+r*size)==0)
            exchange(a,size,++p,i);
        if(compare((char*)a+j*size,(char*)a+r*size)==0)
            exchange(a,size,--q,j);
    }
    exchange(a,size,i,r);
    j=i-1;
    i=i+1;
    int k;
    for(k=l;k<=p;k++)
        exchange(a,size,k,j--);
    for(k=r-1;k>=q;k--)
        exchange(a,size,k,i++);
    sort(a,size,l,j,compare);
    sort(a,size,i,r,compare);
}