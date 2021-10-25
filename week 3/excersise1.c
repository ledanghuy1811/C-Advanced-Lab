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
int Phonecompare(void const *x,void const *y);
int Phonesearch(PhoneEntry a[],int left,int right,char item[]);
void addPhoneNumber(char name[],long number,PhoneBook *a);
PhoneEntry *getPhoneBook(char name[],PhoneBook a);

int main()
{
    PhoneBook book=createPhoneBook();
    int choice;
    char name[80];
    long number;
    do
    {
        printf("--------------MENU-------------\n");
        printf("1.Add Phone Book\n");
        printf("2.Print Phone Book\n");
        printf("3.Find Phone Book\n");
        printf("4.Free Phone Book and exit\n");
        printf("--------------------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter name-number: ");
                scanf("%s %d",name,&number);
                addPhoneNumber(name,number,&book);
                printf("\n");
                break;
            case 2:
                printf("Phone Book-information:\n");
                print(book);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                PhoneEntry *temp=getPhoneBook(name,book);
                if(temp==NULL)
                    printf("Can not find Phone Boook\n\n");
                else
                    printf("Found Entry: %s\t%d\n\n",temp->name,temp->number);
                break;
            case 4:
                printf("Thanks for using menu\n\n");
                dropPhoneBook(&book);
                break;
            default:
                printf("Wrong option. Try again\n\n");
                break;
        }
    }while(choice!=4);
    return 0;
}

PhoneBook createPhoneBook()
{
    PhoneBook a;
    a.entries=(PhoneEntry*)malloc(sizeof(PhoneEntry)*initial_size);
    a.size=initial_size;
    a.total=0;
    return a;
}

void dropPhoneBook(PhoneBook *a)
{
    free(a->entries);
}

void print(PhoneBook a)
{
    int i;
    for(i=0;i<a.total;i++)
        printf("%s\t%d\n",a.entries[i].name,a.entries[i].number);
}

int Phonecompare(void const *x,void const *y)
{
    PhoneEntry m,n;
    m=*((PhoneEntry*)x);
    n=*((PhoneEntry*)y);
    return strcmp(m.name,n.name);
}

int Phonesearch(PhoneEntry a[],int left,int right,char item[])
{
    if(left<=right)
    {
        int mid=(left+right)/2;
        int cmp=strcmp(item,a[mid].name);
        if(cmp==0)
            return mid;
        else if(cmp<0)
            return Phonesearch(a,left,mid-1,item);
        else
            return Phonesearch(a,mid+1,right,item);
    }
    else
        return -1;
}

void addPhoneNumber(char name[],long number,PhoneBook *a)
{
    if(a->total>=a->size)
    {
        a->size=a->size+incremental_size;
        a->entries=(PhoneEntry*)realloc(a->entries,sizeof(PhoneEntry)*(a->size));
    }
    int search=Phonesearch(a->entries,0,a->total-1,name);
    if(search>=0)
        a->entries[search].number=number;
    else
    {
        a->entries[a->total].number=number;
        strcpy(a->entries[a->total].name,name);
        a->total++;
    }
    qsort(a->entries,a->total,sizeof(PhoneEntry),Phonecompare);
}

PhoneEntry *getPhoneBook(char name[],PhoneBook a)
{
    int search=Phonesearch(a.entries,0,a.total-1,name);
    if(search<0)
        return NULL;
    else
        return &a.entries[search];
}