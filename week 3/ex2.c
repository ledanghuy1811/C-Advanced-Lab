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
int PhoneCompare(void const*x,void const*y);
SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*), int (*compare)(void const*,void const*));
void dropSymbolTable(SymbolTable *a);
void print(SymbolTable a);
int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*));
void addEntry(void *key,void *value,SymbolTable *a);
Entry *getEntry(void *key,SymbolTable a);

int main()
{
    SymbolTable book=createSymbolTable(makePhone,PhoneCompare);
    char name[20];
    int number;
    scanf("%s %d",&name,&number);
    addEntry(name,&number,&book);
    scanf("%s %d",&name,&number);
    addEntry(name,&number,&book);
    scanf("%s %d",&name,&number);
    addEntry(name,&number,&book);
    print(book);
    strcpy(name,"Huy");
    Entry *temp=getEntry(name,book);
    printf("%s\t%d\n",temp->key,temp->value);
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

int PhoneCompare(void const*x,void const*y)
{
    Entry m,n;
    m=*((Entry*)x);
    n=*((Entry*)y);
    return strcmp((char*)(m.key),(char*)(n.key));
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*), int (*compare)(void const*,void const*))
{
    SymbolTable a;
    a.entries=(Entry*)malloc(sizeof(Entry)*initial_size);
    a.total=0;
    a.size=initial_size;
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
        printf("%s\t%d\n",(char*)(a.entries[i].key),(int)(a.entries[i].value));
}

int gen_search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*))
{
    if(r<l)
        return -1;
    int mid,cmp;
    mid=(l+r)/2;
    Entry temp=makePhone(item,&mid);
    cmp=compare(&temp,buf+mid*size);
    if(cmp==0)
        return mid;
    else if(cmp<0)
        return gen_search(buf,size,l,mid-1,item,compare);
    else    
        return gen_search(buf,size,mid+1,r,item,compare);
}

void addEntry(void *key,void *value,SymbolTable *a)
{
    if(a->total>=a->size)
    {
        a->size=a->size+incremental_size;
        a->entries=(Entry*)realloc(a->entries,sizeof(Entry)*(a->size));
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
