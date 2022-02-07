#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"jrb.h"
#include"jval.h"
#define INFINITE_VALUE 100000
#define MAX 300

typedef struct 
{
    JRB vertices;
    JRB edges;
}Graph;

typedef struct
{
    Graph graph;
    JRB root;
}HuffmanTree;

typedef struct
{
    int size;
    char bits[30];
}Coding;

typedef struct
{
    int size;
    int *node;
}HuffmanTreeArray;

Graph createGrpah();
JRB enQueue(char *buffer,int size);
JRB findMin(JRB a);
void addVertex(Graph a,int id,int val);
void addEdges1(Graph a,int v1,int v2);   //direction : v1 to v2
void addEdges2(Graph a,int v1,int v2);   //direction : v1 to v2
int inDegree(Graph a,int v,int *output);    //direction to v
int outDegree(Graph a,int v,int *ouput);    //direction out of v
int takeValue(Graph a,int v1,int v2);
HuffmanTree makeHuffman(char *buffer,int size);
void enCode(HuffmanTree a,Coding *b,JRB node,int index,int lenght);
void createHuffmanTable(HuffmanTree htree,Coding *htable);
int findSize(HuffmanTree a);
HuffmanTreeArray tree2Array(HuffmanTree a);
void compress(char buffer[],Coding *htable,char huffman[],int *nbit);
void compressFile(FILE *out,HuffmanTreeArray a,char huffCode[],int size);

int main()
{
    HuffmanTree Htree;
    Coding huffmanTable[MAX];
    HuffmanTreeArray huffArray;
    char change[MAX];
    char string[MAX];
    int size;
    FILE *in,*out;
    in=fopen("input.txt","r");
    fgets(string,sizeof(string),in);
    fclose(in);
    Htree=makeHuffman(string,strlen(string));
    createHuffmanTable(Htree,huffmanTable);
    compress(string,huffmanTable,change,&size);
    huffArray=tree2Array(Htree);
    out=fopen("output1.txt","w");
    compressFile(out,huffArray,change,size);
    fclose(out);
    return 0;
}

Graph createGrpah()
{
    Graph a;
    a.edges=make_jrb();
    a.vertices=make_jrb();
    return a;
}

JRB enQueue(char *buffer,int size)
{
    JRB Queue=make_jrb();
    int i;
    for(i=0;i<size;i++)
    {
        int index=(int)(buffer[i]);
        JRB node=jrb_find_int(Queue,index);
        if(node==NULL)  
            jrb_insert_int(Queue,index,new_jval_i(1));
        else
        {
            int freq=jval_i(node->val);
            freq++;
            jrb_delete_node(node);
            jrb_insert_int(Queue,index,new_jval_i(freq));
        }
    }
    return Queue;
}

JRB findMin(JRB a)
{
    JRB node;
    int check=0;
    jrb_traverse(node,a)
    {
        check++;
    }
    if(check==0)
        return NULL;
    int min=INFINITE_VALUE;
    int index=-1;
    jrb_traverse(node,a)
    {
        if(jval_i(node->val)<min)
        {
            min=jval_i(node->val);
            index=jval_i(node->key);
        }
    }
    return jrb_find_int(a,index);
}

void addVertex(Graph a,int id,int val)
{
    JRB node=jrb_find_int(a.vertices,id);
    if(node==NULL)
        jrb_insert_int(a.vertices,id,new_jval_i(val));
}

void addEdges1(Graph a,int v1,int v2)   //direction : v1 to v2
{
    JRB temp=make_jrb();
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)      //node v1 has no edges
        jrb_insert_int(a.edges,v1,new_jval_v(temp));
    else
        temp=(JRB)jval_v(node->val);
    jrb_insert_int(temp,v2,new_jval_i(0));
}

void addEdges2(Graph a,int v1,int v2)   //direction : v1 to v2
{
    JRB temp=make_jrb();
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)      //node v1 has no edges
        jrb_insert_int(a.edges,v1,new_jval_v(temp));
    else
        temp=(JRB)jval_v(node->val);
    jrb_insert_int(temp,v2,new_jval_i(1));
}

int inDegree(Graph a,int v,int *output)    //direction to v
{
    int total=0;
    JRB node;
    jrb_traverse(node,a.edges)
    {
        int check=0;
        JRB temp,tree;
        tree=(JRB)jval_v(node->val);
        jrb_traverse(temp,tree)
        {
            if(jval_i(temp->key)==v)
                check=1;
        }
        if(check)
        {
            output[total]=jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outDegree(Graph a,int v,int *ouput)
{
    int total=0;
    JRB node=jrb_find_int(a.edges,v);
    if(node==NULL)
        return 0;
    JRB temp,tree;
    tree=(JRB)jval_v(node->val);
    jrb_traverse(temp,tree)
    {
        ouput[total]=jval_i(temp->key);
        total++;
    }
    return total;
}

int takeValue(Graph a,int v1,int v2)
{
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)
        return -1;
    JRB temp=(JRB)jval_v(node->val);
    node=jrb_find_int(temp,v2);
    if(node==NULL)
        return -1;
    return jval_i(node->val);
}

HuffmanTree makeHuffman(char *buffer,int size)
{
    int mark=300;
    // implement Huffman Tree
    HuffmanTree H;
    H.graph=createGrpah();
    H.root=make_jrb();
    // enqueue
    JRB Queue=enQueue(buffer,size);
    // make Huffman tree
    JRB node1,node2;
    while(1)
    {
        // edit node 1
        node1=findMin(Queue);
        H.root=node1;
        int freq1=jval_i(node1->val);
        int key1=jval_i(node1->key);
        jrb_delete_node(node1);
        // edit node 2
        node2=findMin(Queue);
        if(node2==NULL)
            break;
        int freq2=jval_i(node2->val);
        int key2=jval_i(node2->key);
        jrb_delete_node(node2);
        // add vertex
        addVertex(H.graph,key1,1);
        addVertex(H.graph,key2,1);
        jrb_insert_int(Queue,mark,new_jval_i(freq1+freq2));
        addVertex(H.graph,mark,0);
        // add edges
        addEdges1(H.graph,mark,key1);
        addEdges2(H.graph,mark,key2);
        mark++;
    }
    return H;
}

void enCode(HuffmanTree a,Coding *b,JRB node,int index,int lenght)
{
    int output[MAX];
    memset(output,0,sizeof(output));
    int total=inDegree(a.graph,jval_i(node->key),output);
    if(total==0)
    {
        b[index].bits[lenght]='\0';
        strrev(b[index].bits);
        return;
    }
    b[index].size++;
    if(takeValue(a.graph,output[total-1],jval_i(node->key))==1)
        b[index].bits[lenght]='1';
    else    
        b[index].bits[lenght]='0';
    lenght++;
    node=jrb_find_int(a.graph.vertices,output[total-1]);
    enCode(a,b,node,index,lenght);
}

void createHuffmanTable(HuffmanTree htree,Coding *htable)
{
    int i;
    for(i=0;i<MAX;i++)
        htable[i].size=0;
    JRB node;
    JRB Tree=make_jrb();
    int output[MAX];
    memset(output,0,sizeof(output));
    jrb_traverse(node,htree.graph.vertices)
    {
        if(outDegree(htree.graph,jval_i(node->key),output)==0)
            jrb_insert_int(Tree,jval_i(node->key),new_jval_i(1));
    }
    jrb_traverse(node,Tree)
    {
        int index=jval_i(node->key);
        htable[index].size=0;
        int lenght=0;
        enCode(htree,htable,node,index,lenght);
    }
}

int findSize(HuffmanTree a)
{
    int output[MAX];
    int array[MAX];
    int total=0;
    memset(output,0,sizeof(output));
    memset(array,0,sizeof(array));
    int size=0;
    total=outDegree(a.graph,jval_i(a.root->key),array);
    size++;
    while(total!=0)
    {
        int total1=0;
        int total2=0;
        int arrayTemp[MAX];
        memset(arrayTemp,0,sizeof(arrayTemp));
        int i,j;
        for(i=0;i<total;i++)
        {
            total1=outDegree(a.graph,array[i],output);
            for(j=0;j<total1;j++)
            {
                arrayTemp[total2]=output[j];
                total2++;
            }
        }
        total=total2;
        for(j=0;j<total;j++)
            array[j]=arrayTemp[j];
        size++;
    }
    return size;
}

HuffmanTreeArray tree2Array(HuffmanTree a)
{
    HuffmanTreeArray array;
    int output[MAX];
    memset(output,0,sizeof(output));
    int size=findSize(a);
    int i,sum=0;
    for(i=0;i<size;i++)
        sum+=pow(2,i);
    array.size=sum;
    array.node=(int*)malloc(sizeof(int)*array.size);
    int index=0;
    array.node[0]=jval_i(a.root->key);
    while(1)
    {
        if(index==array.size)
            break;
        int total=outDegree(a.graph,array.node[index],output);
        if((2*index+2)<=array.size && (2*index+1)<=array.size)
        {
            if(total==0)
            {
                array.node[2*index+1]=-2;
                array.node[2*index+2]=-2;
            }
            else
                for(i=0;i<total;i++)
                {
                    if(takeValue(a.graph,array.node[index],output[i])==0)
                        array.node[2*index+1]=output[i];
                    else
                        array.node[2*index+2]=output[i];
                }
        }
        index++;
    }
    return array;
}

void compress(char buffer[],Coding *htable,char huffman[],int *nbit)
{
    int size=0;
    int i;
    int lenght=strlen(buffer);
    for(i=0;i<lenght;i++)
    {
        int index=(int)(buffer[i]);
        if(i==0)
            strcpy(huffman,htable[index].bits);
        else
            strcat(huffman,htable[index].bits);
        size+=htable[index].size;
    }
    *nbit=size;
}

void compressFile(FILE *out,HuffmanTreeArray a,char huffCode[],int size)
{
    fprintf(out,"%s","HM ");
    printf("%s","HM ");
    int i;
    for(i=0;i<a.size;i++)
    {
        if(a.node[i]<0)
        {
            fprintf(out,"%c",'*');
            printf("*");
        }
        else if(a.node[i]>=0 && a.node[i]<=256)
        {
            fprintf(out,"%c",(char)a.node[i]);
            printf("%c",a.node[i]);
        }
        else
        {
            fprintf(out,"%d",-1);
            printf("-1");
        }
    }
    fprintf(out,"%c",' ');
    printf(" ");
    fprintf(out,"%d",size);
    printf("%d",size);
    fprintf(out,"%c",' ');
    printf(" ");
    fprintf(out,"%s",huffCode);
    printf("%s\n",huffCode);
}