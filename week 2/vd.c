#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef union
{
    int i;
    float f;
}jval; //make fundamental javl has 2 elements int and float

jval new_jval_i(int a);
void rand_function(jval a[],int n);
void print(jval a[],int n);
int int_compare(jval *a,jval *b);
int search(jval a[],int l,int r,jval *item,int (*compare)(jval*,jval*));
void swap(jval a[],int i,int j);
void sort(jval a[],int l,int r,int (*compare)(jval*,jval*));

int main()
{
    int n=10;
    jval item=new_jval_i(8);
    jval *arr=(jval*)malloc(sizeof(jval)*n);
    rand_function(arr,n);
    print(arr,n);
    sort(arr,0,n-1,int_compare);
    print(arr,n);
    int res=search(arr,0,n-1,&item,int_compare);
    printf("%d\n",res);
    return 0;
}

jval new_jval_i(int a)
{
    jval x;
    x.i=a;
    return x;
}

void rand_function(jval a[],int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
        a[i]=new_jval_i(rand()%10+1);
}

void print(jval a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i].i);
    printf("\n");
}

int int_compare(jval *a,jval *b)
{
    jval m,n;
    m=*a,n=*b;
    if(m.i==n.i)
        return 0;
    return m.i>n.i ? 1:-1;
}

int search(jval a[],int l,int r,jval *item,int (*compare)(jval*,jval*))
{
    int i,res;
    if(r<l)
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

void swap(jval a[],int i,int j)
{
    jval temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

void sort(jval a[],int l,int r,int (*compare)(jval*,jval*))
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
    sort(a,l,j,compare);
    sort(a,i,r,compare);
}