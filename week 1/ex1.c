#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void randfunnction(int a[],int n);
void print(int a[],int n);
void swap(int *a, int *b);
int partition_2way(int a[],int low,int high);
void quicksort2way(int a[],int low,int high);
void partition3way(int a[],int low,int high,int *i,int *j);
void quicksort3way(int a[],int low,int high);

int main()
{
    int n=1000000;
    clock_t start,end;
    double time_use;
    int *arr1=(int*)malloc(n*sizeof(int));
    int *arr2=(int*)malloc(n*sizeof(int));
    randfunnction(arr1,n);
    memcpy(arr2,arr1,sizeof(int)*n);
    start=clock();
    quicksort2way(arr1,0,n-1);
    end=clock();
    time_use=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time for sorting 2-way partitioning is: %f\n",time_use);
    start=clock();
    quicksort3way(arr2,0,n-1);
    end=clock();
    time_use=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time for sorting 3-way partitioning is: %f\n",time_use);
    return 0;
}

void randfunnction(int a[],int n)
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

void quicksort2way(int a[],int low,int high)
{
    if(low<high)
    {
        int pi=partition_2way(a,low,high);
        quicksort2way(a,low,pi-1);
        quicksort2way(a,pi+1,high);
    }
}

void partition3way(int a[],int low,int high,int *i,int *j)
{
    int x=low-1,y=high;
    int left=low-1,right=high;
    int pivot=a[high];
    while(1)
    {
        while(a[++x]<pivot);
        while(a[--y]>pivot)
        {
            if(y==low)
                break;
        }
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
    for(k=high-1;k>right;k--,x++)
        swap(&a[x],&a[k]);
    *i=x;
    *j=y;
}

void quicksort3way(int a[],int low,int high)
{
    if(low<high)
    {
        int i,j;
        partition3way(a,low,high,&i,&j);
        quicksort3way(a,low,j);
        quicksort3way(a,i,high);
    }
}