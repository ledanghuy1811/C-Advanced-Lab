#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define initial_size 10
#define incremental_size 5

typedef struct
{
    char name[80];
    long number;
}PhoneEntry;

typedef struct
{
    PhoneEntry *entries;
    int total;
    int size;
}PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook *a);
void print(PhoneBook a);
int PhoneEntry_compare(void const *x,void const *y);
int binarysearch(PhoneEntry a[],int low,int high,char *item);
void addPhoneNumber(char name[],long number,PhoneBook *a);
PhoneEntry *getPhoneNumber(char name[],PhoneBook a);

int main()
{
    PhoneBook book;
    book=createPhoneBook();
    /*addPhoneNumber("Huy",1905,&book);
    addPhoneNumber("Hang",1905,&book);
    addPhoneNumber("Anh",1905,&book);
    print(book);*/
    int choice;
    long number;
    char name[80];
    do
    {
        printf("-------------------MENU-----------------\n");
        printf("1.Add entries\n");
        printf("2.Print entries\n");
        printf("3.Find entries\n");
        printf("4.Drop entries and exit\n");
        printf("-----------------------------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter name-number: ");
                scanf("%s %d",&name,&number);
                addPhoneNumber(name,number,&book);
                printf("\n");
                break;
            case 2:
                printf("List of entries:\n");
                print(book);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                PhoneEntry *temp=getPhoneNumber(name,book);
                if(temp==NULL)
                    printf("Can not find entries\n\n");
                else
                    printf("Find entries: %s\t%d\n\n",temp->name,temp->number);
                break;
            case 4:
                printf("Thanks for using\n\n");
                dropPhoneBook(&book);
                break;
            default:
                printf("Wrong option\n\n");
                break;
        }
    }while(choice!=4);
    return 0;
}

PhoneBook createPhoneBook()
{
    PhoneBook a;
    a.entries=(PhoneEntry*)malloc(sizeof(PhoneEntry)*initial_size);
    a.total=0;
    a.size=initial_size;
    return a;
}

void dropPhoneBook(PhoneBook *a)
{
    free((*a).entries);
}

void print(PhoneBook a)
{
    int i;
    for(i=0;i<a.total;i++)
        printf("%s\t%d\n",a.entries[i].name,a.entries[i].number);
}

int PhoneEntry_compare(void const *x,void const *y)
{
    PhoneEntry a,b;
    a=*((PhoneEntry*)x);
    b=*((PhoneEntry*)y);
    return strcmp(a.name,b.name);
}

int binarysearch(PhoneEntry a[],int low,int high,char *item)
{
    if(low<=high)
    {
        int mid=(low+high)/2;
        int cmp=strcmp(a[mid].name,item);
        if(cmp==0)
            return mid;
        else if(cmp>0)
            return binarysearch(a,low,mid-1,item);
        else
            return binarysearch(a,mid+1,high,item);
    }
    else   
        return -1;
}

void addPhoneNumber(char name[],long number,PhoneBook *a)
{
    if((a->total)>=(a->size))
    {
        PhoneEntry *b=(PhoneEntry*)malloc(sizeof(PhoneEntry)*(a->total));
        memcpy(b,a->entries,sizeof(PhoneEntry)*(a->total));
        a->size=a->size+incremental_size;
        a->entries=(PhoneEntry*)malloc(sizeof(PhoneEntry)*(a->size));
        memcpy(a->entries,b,sizeof(PhoneEntry)*(a->total));
        free(b);
    }
    int search=binarysearch(a->entries,0,a->total-1,name);
    if(search>=0)
    {
        a->entries[search].number=number;
        strcpy(a->entries[search].name,name);
    }
    else
    {
        a->entries[a->total].number=number;
        strcpy(a->entries[a->total].name,name);
        a->total++;
    }
    qsort(a->entries,a->total,sizeof(PhoneEntry),PhoneEntry_compare);
}

PhoneEntry *getPhoneNumber(char name[],PhoneBook a)
{
    int search=binarysearch(a.entries,0,a.total-1,name);
    if(search<0)
        return NULL;
    return &a.entries[search];
}