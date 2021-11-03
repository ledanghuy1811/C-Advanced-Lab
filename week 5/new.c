#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"btree.h"
#define max_size 10


int menu();
void print(BTA *a,char root[]);
int addPhoneBook(BTA *a,char name[],char data[],int *check,char rootname[]);
int deletePhoneBook(BTA *a,char name[],char rootname[]);

int main()
{
    char filename[30],rootname[30];
    char key[30],data[30];
    int check,choice,value,val=0;
    BTint a;
    printf("Enter file name: ");
    fflush(stdin);
    gets(filename);
    // initialize
    btinit();
    BTA *PhoneBook;
    // Open B-tree
    PhoneBook=btopn(filename,0,0);
    if(PhoneBook==NULL)
        PhoneBook=btcrt(filename,3,0);
    do
    {
        choice=menu();
        switch(choice)
        {
            case 1:
                printf("Enter key-data: ");
                scanf("%s %s",key,data);
                check=addPhoneBook(PhoneBook,key,data,&val,rootname);
                if(check==0)
                    printf("Insert successfully\n\n");
                else
                    printf("Insert unseccessfully\n\n");
                break;
            case 2:
                printf("List of Phone Book:\n");
                print(PhoneBook,rootname);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                while(getchar()!='\n');
                gets(key);
                check=btsel(PhoneBook,key,data,sizeof(char)*max_size,&value);
                if(check==0)
                    printf("Found name: %s-%s\n\n",key,data);
                else
                    printf("Can not find name: %s\n\n",data);
                break;
            case 4:
                printf("Enter name: ");
                while(getchar()!='\n');
                gets(key);
                check=deletePhoneBook(PhoneBook,key,rootname);
                if(check==1)
                    printf("Delete successfully\n\n");
                else
                    printf("Delete unsuccessfully\n\n");
                break;
            case 5:
                printf("Thanks for using\n\n");
                break;
            default:
                printf("Wrong option\n\n");
                break;
        }
    }while(choice!=5);
    // Close b-tree
    btcls(PhoneBook);
    return 0;
}

int menu()
{
    int choice;
    printf("-------------MENU-----------\n");
    printf("1. Add Phone Book\n");
    printf("2. Print Phone Book\n");
    printf("3. Find Phone Book\n");
    printf("4. Delete Phone Book\n");
    printf("5. Exit\n");
    printf("-----------------------------\n\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    return choice;
}

void print(BTA *a,char root[])
{
    int i,val;
    char key[30],data[30];
    btsel(a,root,data,sizeof(char)*max_size,&val);
    data[val/sizeof(char)+1]='\0';
    printf("%s\t%s\n",root,data);
    i=btseln(a,key,data,sizeof(char)*max_size,&val);
    data[val/sizeof(char)+1]='\0';
    while(i==0)
    {
        data[val/sizeof(char)+1]='\0';
        printf("%s\t%s\n",key,data);
        i=btseln(a,key,data,sizeof(char)*max_size,&val);
    }
}

int addPhoneBook(BTA *a,char name[],char data[],int *check,char rootname[])
{
    if(*check==0)
    {
        strcpy(rootname,name);
        *check=1;
    }
    else
    {
        int i=strcmp(name,rootname);
        if(i<0)
            strcpy(rootname,name);
    }
    return btins(a,name,data,sizeof(char)*strlen(data));
}

int deletePhoneBook(BTA *a,char name[],char rootname[])
{
    int check,rsize;
    BTint b;
    char temp[30],datatemp[30];
    check=bfndky(a,name,&b);
    if(check==0)
    {
        if(strcmp(rootname,name)==0)
        {
            btsel(a,rootname,datatemp,sizeof(char)*max_size,&rsize);
            btseln(a,temp,datatemp,sizeof(char)*max_size,&rsize);
            strcpy(rootname,temp);
        }
        check=btdel(a,name);
        return 1;
    }
    else
    {
        printf("Can not find name: %s\n",name);
        return 0;
    }
}