#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void randfunction(int a[],int n);
void print(int a[],int n);
void swap(int *a,int *b);
int partition_2way(int a[],int low,int high);
void quicksort_2way(int a[],int low,int high);
void partition_3way(int a[],int low,int high,int *i,int *j);
void quicksort_3way(int a[],int low,int high);
int int_compare(void const *x,void const *y);

int main()
{
    int n=10;
    clock_t start,end;
    double time_use;
    int *arr1=(int*)malloc(sizeof(int)*n);
    int *arr2=(int*)malloc(sizeof(int)*n);
    int *arr3=(int*)malloc(sizeof(int)*n);
    randfunction(arr1,n);
    memcpy(arr2,arr1,sizeof(int)*n);
    memcpy(arr3,arr1,sizeof(int)*n);
    print(arr1,n);
    //quicksort_3way(arr1,0,n-1);
    qsort(arr1,n,sizeof(int),int_compare);
    print(arr1,n);
    return 0;
}

void randfunction(int a[],int n)
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

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int partition_2way(int a[],int low,int high)
{
    int pivot=a[high];
    int left=low;
    int right=high-1;
    while(1)
    {
        while(left<=right && a[left]<pivot)
            left++;
        while(left<=right && a[right]>pivot)
            right--;
        if(left>=right)
            break;
        swap(&a[left],&a[right]);
        left++;
        right--;
    }
    swap(&a[left],&a[high]);
    return left;
}

void quicksort_2way(int a[],int low,int high)
{
    if(low<high)
    {
        int pi=partition_2way(a,low,high);
        quicksort_2way(a,low,pi-1);
        quicksort_2way(a,pi+1,high);
    }
}

void partition_3way(int a[],int low,int high,int *i,int *j)
{
    int x=low-1,y=high;
    int left=low-1,right=high;
    int pivot=a[high];
    while(1)
    {
        while(a[++x]<pivot);
        while(a[--y]>pivot)
            if(y==low)
                break;
        if(x>=y)
            break;
        swap(&a[x],&a[y]);
        if(a[x]==pivot)
        {
            left++;
            swap(&a[x],&a[left]);
        }      
        if(a[y]==pivot)
        {
            right--;
            swap(&a[y],&a[right]);
        }
    }
    swap(&a[x],&a[high]);
    y=x-1;
    int k;
    for(k=low;k<left;k++,y--)
        swap(&a[k],&a[y]);
    x=x+1;
    for(k=high-1;k>right;k++,x++)
        swap(&a[k],&a[x]);
    *i=x;
    *j=y;
}

void quicksort_3way(int a[],int low,int high)
{
    if(low<high)
    {
        int i,j;
        partition_3way(a,low,high,&i,&j);
        quicksort_3way(a,low,j);
        quicksort_3way(a,i,high);
    }
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