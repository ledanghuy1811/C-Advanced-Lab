#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void print(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
    printf("\n");
}

int main()
{
    /*int *a=(int*)malloc(sizeof(int)*5);
    int *b=(int*)malloc(sizeof(int)*10);
    int i;
    srand(time(NULL));
    for(i=0;i<5;i++)
        a[i]=rand()%100+1;
    memcpy(b,a,sizeof(int)*5);
    print(a,5);
    free(a);
    print(b,10);*/
    char s[20],c[20],b[20];
    strcpy(b,"hang");
    strcpy(s,"huy");
    strcpy(c,"anh");
    // printf("%d\n%d\n%d\n",(int)s,(int)b,(int)c);
    printf("%d\n",strcmp("hang","hang"));
    return 0;
}