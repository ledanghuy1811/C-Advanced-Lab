#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void create_array(int a[],int n);
void print_array(int a[],int n);
int int_compare(void const *x,void const *y);
void exchange(void *buf,int size,int i,int j);
void gen_sort(void *buf,int size,int l,int r,int (*compare)(void const*,void const*));

int main()
{
    int n=10;
    int *arr=(int*)malloc(sizeof(int)*n);
    create_array(arr,n);
    printf("Array before sorting:\n");
    print_array(arr,n);
    gen_sort(arr,sizeof(int),0,n-1,int_compare);
    printf("Array after sorting:\n");
    print_array(arr,n);
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

void exchange(void *buf,int size,int i,int j)
{
    char temp=*((char*)(buf+size*i));
    *((char*)(buf+size*i))=*((char*)(buf+size*j));
    *((char*)(buf+size*j))=temp;
}

void gen_sort(void *buf,int size,int l,int r,int (*compare)(void const*,void const*))
{
    if(r<=l)
        return;
    int i=l-1,j=r;
    int p=l-1,q=r;
    while(1)
    {
        while(compare((char*)(buf+(++i)*size),(char*)(buf+r*size))<0);
        while(compare((char*)(buf+(--j)*size),(char*)(buf+r*size))>0)
            if(j==l)
                break;
        if(i>=j)
            break;
        exchange(buf,size,i,j);
        if(compare((char*)(buf+i*size),(char*)(buf+r*size))==0)
            exchange(buf,size,++p,i);
        if(compare((char*)(buf+j*size),(char*)(buf+r*size))==0)
            exchange(buf,size,--q,j);
    }
    exchange(buf,size,i,r);
    j=i-1;
    i=i+1;
    int k;
    for(k=l;k<=p;k++)   
        exchange(buf,size,k,j--);
    for(k=r-1;k>=q;k--)
        exchange(buf,size,k,i++);
    gen_sort(buf,size,l,j,compare);
    gen_sort(buf,size,i,r,compare);
}