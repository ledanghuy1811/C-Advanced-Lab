#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jval.h"

int menu();
void print(JRB a);
void addPhoneBook(JRB a,char name[],long number);
void deletePhoneNumber(JRB a,char name[]);
void modifyPhoneBook(JRB a,char name[]);
void makeFile(JRB a,char filename[]);

int main()
{
    JRB PhoneBook=make_jrb();
    char name[20];
    long number;
    int choice;
    do
    {
        choice=menu();
        switch(choice)
        {
            case 1:
                printf("Enter name-number: ");
                scanf("%s %ld",name,&number);
                addPhoneBook(PhoneBook,name,number);
                printf("\n");
                break;
            case 2: 
                printf("List of Phone Book:\n");
                print(PhoneBook);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                deletePhoneNumber(PhoneBook,name);
                print(PhoneBook);
                printf("\n");
                break;
            case 4:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                modifyPhoneBook(PhoneBook,name);
                print(PhoneBook);
                printf("\n");
                break;
            case 5:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                makeFile(PhoneBook,name);
                printf("\n");
                break;
            case 6:
                printf("Thanks for using\n\n");
                jrb_free_tree(PhoneBook);
                break;
            default:
                printf("Wrong option\n\n");
                break;
        }
    }while(choice!=6);
    return 0;
}

int menu()
{
    int choice;
    printf("------------MENU----------\n");
    printf("1. Add Phone Book\n");
    printf("2. Print Phone Book\n");
    printf("3. Delete Phone Book\n");
    printf("4. Modify Phone Book\n");
    printf("5. Make file for Phone Book\n");
    printf("6. Free all Phone Book and Exit\n");
    printf("---------------------------\n\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    return choice;
}

void print(JRB a)
{
    JRB temp;
    jrb_traverse(temp,a)
    {
        printf("%s\t%ld\n",jval_s(temp->key),jval_l(temp->val));
    }
}

void addPhoneBook(JRB a,char name[],long number)
{
    JRB temp=jrb_find_str(a,name);
    if(temp==NULL)
        jrb_insert_str(a,strdup(name),new_jval_l(number));
    else
        temp->val=new_jval_l(number);
}

void deletePhoneNumber(JRB a,char name[])
{
    JRB temp=jrb_find_str(a,name);
    if(temp==NULL)
        printf("Can not find node: %s\n",name);
    else
        jrb_delete_node(temp);
}

void modifyPhoneBook(JRB a,char name[])
{
    long number;
    JRB temp=jrb_find_str(a,name);
    if(temp==NULL)
        printf("Can not find node: %s\n",name);
    else
    {
        printf("Enter number: ");
        scanf("%ld",&number);
        temp->val=new_jval_l(number);
    }
}

void makeFile(JRB a,char filename[])
{
    FILE *f;
    JRB temp;
    f=fopen(filename,"w");
    jrb_traverse(temp,a)
    {
        fprintf(f,"%s \t %ld\n",jval_s(temp->key),jval_l(temp->val));
    }
    fclose(f);
}