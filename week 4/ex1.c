#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"

void print(JRB a);

int main()
{
    JRB PhoneBook=make_jrb();
    JRB temp;
    FILE *f;
    char name[20];
    long number;
    int choice;
    do
    {
        printf("------------MENU---------\n");
        printf("1. Add Phone Book\n");
        printf("2. Print Phone Book\n");
        printf("3. Delete Phone Book\n");
        printf("4. Modify Phone Book\n");
        printf("5. Make file Phone Book\n");
        printf("6. Free all and exit\n");
        printf("--------------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter name-number: ");
                fflush(stdin);
                scanf("%s %ld",name,&number);
                temp=jrb_find_str(PhoneBook,name);
                if(temp==NULL)
                    jrb_insert_str(PhoneBook,name,new_jval_l(number));
                else
                    temp->key=new_jval_l(number);
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
                temp=jrb_find_str(PhoneBook,name);
                if(temp==NULL)
                    printf("Can not find %s\n\n",name);
                else
                {
                    jrb_delete_node(temp);
                    print(PhoneBook);
                    printf("\n");
                }
                break;
            case 4:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                temp=jrb_find_str(PhoneBook,name);
                if(temp==NULL)
                    printf("Can not find %s\n\n",name);
                else
                {
                    printf("Enter number: ");
                    scanf("%ld",&number);
                    temp->key.l=number;
                    print(PhoneBook);
                }
                break;
            case 5:
                printf("Enter file name: ");
                fflush(stdin);
                gets(name);
                f=fopen(name,"w");
                jrb_traverse(temp,PhoneBook)
                {
                    fprintf(f,"%s\t%ld\n",jval_s(temp->key),jval_l(temp->val));
                }
                fclose(f);
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
    print(PhoneBook);
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

