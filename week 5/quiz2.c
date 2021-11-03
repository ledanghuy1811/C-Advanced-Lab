#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"btree.h"

int menu();
int addPhoneBook(BTA *a,char name[],char data[]);
int deletePhoneBook(BTA *a,char name[]);

int main()
{
    char filename[30];
    char name[30],data[30];
    int check,choice;
    BTint a;
    printf("Enter name of file: ");
    fflush(stdin);
    gets(filename);
    // initialize b-tree
    btinit();
    BTA *PhoneBook;
    // Open b-tree
    PhoneBook=btopn(filename,0,0);
    if(PhoneBook==NULL)
        PhoneBook=btcrt(filename,3,0);
    do
    {
        choice=menu();
        switch(choice)
        {
            case 1:
                printf("Enter name and data: ");
                scanf("%s %s",name,data);
                check=addPhoneBook(PhoneBook,name,data);
                if(check==0)
                    printf("Insert successfully\n\n");
                else
                    printf("Insert unseccessfully\n\n");
                break;
            case 2:
                printf("Enter name: ");
                while(getchar()!='\n');
                gets(name);
                check=bfndky(PhoneBook,name,&a);
                if(check==0)
                    printf("Found name: %s\n\n",name);
                else
                    printf("Can not find name: %s\n\n",name);
                break;
            case 3:
                printf("Enter name: ");
                while(getchar()!='\n');
                gets(name);
                check=deletePhoneBook(PhoneBook,name);
                if(check==1)
                    printf("Delete successfully\n\n");
                else
                    printf("Delete unsuccessfully\n\n");
                break;
            case 4:
                printf("Thanks for using\n\n");
                break;
            default:
                printf("Wrong option\n\n");
                break;
        }
    }while(choice!=4);
    // Close b-tree
    btcls(PhoneBook);
    return 0;
}

int menu()
{
    int choice;
    printf("-----------MENU-----------\n");
    printf("1. Add key and data\n");
    printf("2. Find key\n");
    printf("3. Delete key and data\n");
    printf("4. Exit\n");
    printf("---------------------------\n\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    return choice;
}

int addPhoneBook(BTA *a,char name[],char data[])
{
    return btins(a,name,data,sizeof(char)*strlen(data));
}

int deletePhoneBook(BTA *a,char name[])
{
    int check;
    BTint b;
    check=bfndky(a,name,&b);
    if(check==0)
    {
        check=btdel(a,name);
        return 1;
    }
    else
    {
        printf("Can not find name: %s\n",name);
        return 0;
    }
}