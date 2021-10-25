#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"

void print(JRB a);
void addPhoneBook(JRB a,char name[],long number);
void deletePhoneBook(JRB a,char name[]);
void changePhoneBook(JRB a,char name[]);
void export_to_file(JRB a,char filename[]);

int main()
{
    JRB PhoneBook=make_jrb();
    JRB temp;
    int choice;
    long number;
    char name[20];
    do
    {
        printf("---------MENU-------\n");
        printf("1.Add Phone Number\n");
        printf("2.Print Phone Number\n");
        printf("3.Delete Phone Number\n");
        printf("4.Modify Phone Number\n");
        printf("5.Make file Phone Book\n");
        printf("6.Free Phone Book and exit\n");
        printf("---------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter name-number: ");
                scanf("%s %ld",name,&number);
                addPhoneBook(PhoneBook,name,number);
                printf("\n");
                break;
            case 2:
                printf("Information of Phone Book:\n");
                print(PhoneBook);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                deletePhoneBook(PhoneBook,name);
                printf("\n");
                break;
            case 4:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                changePhoneBook(PhoneBook,name);
                printf("\n");
                break;
            case 5:
                printf("Export Phone Book to a file\n");
                printf("Enter file name: ");
                fflush(stdin);
                gets(name);
                export_to_file(PhoneBook,name);
                printf("\n");
                break;
            case 6:
                printf("Thanks for using menu\n\n");
                jrb_free_tree(PhoneBook);
                break;
            default:
                printf("Wrong option. Try again\n\n");
                break;
        }
    }while(choice!=6);
    return 0;
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
    JRB temp;
    temp=jrb_find_str(a,name);
    if(temp==NULL)
        jrb_insert_str(a,strdup(name),new_jval_l(number));
    else
        temp->val=new_jval_l(number);
}

void deletePhoneBook(JRB a,char name[])
{
    JRB temp;
    temp=jrb_find_str(a,name);
    if(temp==NULL)
        printf("Can not find the name: %s\n",name);
    else
    {
        jrb_delete_node(temp);
        printf("Deleted\n");
        print(a);
    }
}

void changePhoneBook(JRB a,char name[])
{
    JRB temp;
    int number;
    temp=jrb_find_str(a,name);
    if(temp==NULL)
        printf("Can not find the name: %s\n",name);
    else
    {
        printf("Found name: %s\n",name);
        printf("Enter new number: ");
        scanf("%ld",&number);
        temp->val=new_jval_l(number);
        print(a);
    }
}

void export_to_file(JRB a,char filename[])
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