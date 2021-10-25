#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define initial_size 10
#define incremental_size 5

typedef struct
{
    void *key;
    void *value;
}Entry;

typedef struct
{
    Entry *entries;
    int size,total;
    Entry (*makeNode)(void*,void*);
    int (*compare)(void const*,void const*);
}SymbolTable;

Entry makePhone(void *key,void *value);
int PhoneCompare(void const *x, void const *y);
SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*),int (*compare)(void const*,void const*));
void dropSymbolTable(SymbolTable *a);
void print(SymbolTable a);
int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*));
void addEntry(void *key,void *value,SymbolTable *a);
Entry *getEntry(void *key,SymbolTable a);

int main()
{
    SymbolTable book;
    book=createSymbolTable(makePhone,PhoneCompare);
    int choice;
    char name[80];
    long number;
    do
    {
        printf("------------MENU----------\n");
        printf("1.Add Entry\n");
        printf("2.Print Entry\n");
        printf("3.Find Entry\n");
        printf("4.Free Entries and exit\n");
        printf("---------------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {  
            case 1:
                printf("Enter name-number: ");
                scanf("%s %d",name,&number);
                // printf("1\n");
                addEntry(name,&number,&book);
                printf("\n");
                break;
            case 2:
                printf("Entries-Information:\n");
                print(book);
                printf("\n");
                break;
            case 3:
                printf("Enter name: ");
                fflush(stdin);
                gets(name);
                Entry *temp=getEntry(name,book);
                if(temp==NULL)
                    printf("Can not find Entry\n\n");
                else
                    printf("Found Entry: %s\t%d\n\n",(char*)temp->key,(long)temp->value);
                break;
            case 4:
                printf("Thanks for using MENU\n\n");
                break;
            default:
                printf("Wrong options. Try again\n\n");
                break;
        }
    }while(choice!=4);
    return 0;
}

Entry makePhone(void *key,void *value)
{
    Entry a;
    a.key=strdup((char*)key);
    a.value=malloc(sizeof(long));
    memcpy(&(a.value),value,sizeof(long));
    return a;
}

int PhoneCompare(void const *x, void const *y)
{
    Entry m,n;
    m=*((Entry*)x);
    n=*((Entry*)y);
    return strcmp((char*)m.key,(char*)n.key);
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*),int (*compare)(void const*,void const*))
{
    SymbolTable a;
    a.entries=(Entry*)malloc(sizeof(Entry)*initial_size);
    a.size=initial_size;
    a.total=0;
    a.makeNode=makeNode;
    a.compare=compare;
    return a;
}

void dropSymbolTable(SymbolTable *a)
{
    free(a->entries);
}

void print(SymbolTable a)
{
    int i;
    for(i=0;i<a.total;i++)
        printf("%s\t%d\n",(char*)a.entries[i].key,(long)a.entries[i].value);
}

int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*))
{
    if(l<=r)
    {
        int mid=(l+r)/2;
        Entry temp=makePhone(item,&mid);
        int cmp=compare(&temp,buf+mid*size);
        if(cmp==0)
            return mid;
        else if(cmp<0)
            return gen_search(buf,size,l,mid-1,item,compare);
        else
            return gen_search(buf,size,mid+1,r,item,compare);
    }
    else
        return -1;
}

void addEntry(void *key,void *value,SymbolTable *a)
{
    if(a->total>=a->size)
    {
        a->size=a->size+incremental_size;
        a->entries=(Entry*)realloc(a->entries,sizeof(Entry)*a->size);
    }
    int search=gen_search(a->entries,sizeof(Entry),0,a->total-1,key,PhoneCompare);
    Entry temp=makePhone(key,value);
    if(search>=0)
        a->entries[search]=temp;
    else
    {
        a->entries[a->total]=temp;
        a->total++;
    }
    qsort(a->entries,a->total,sizeof(Entry),PhoneCompare);
}

Entry *getEntry(void *key,SymbolTable a)
{
    int search=gen_search(a.entries,sizeof(Entry),0,a.total-1,key,PhoneCompare);
    if(search<0)
        return NULL;
    else
        return &(a.entries[search]);
}