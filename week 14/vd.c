#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *f;
    int id1,id2;
    f=fopen("dothi.txt","r");
    fscanf(f,"%d%d",&id1,&id2);
    fclose(f);
    printf("%d %d\n",id1,id2);
    return 0;
}