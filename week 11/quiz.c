#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jval.h"
#define INFINITE_VALUE 1000000
#define MAX 100
int number_of_vertex=8;

typedef struct
{
    JRB vertices;
    JRB edges;  
}Graph;

typedef struct
{
    int vertex;
    double distance;
    int parent;
}Node;

Graph createGrpah();
void addVertex(Graph a,int id,char name[]);
void addEdges(Graph a,int v1,int v2,double weight);   //direction : v1 to v2
double getEdgesValue(Graph a,int v1,int v2);
int inDegree(Graph a,int v,int *output);    //direction to v
int outDegree(Graph a,int v,int *ouput);    //direction out of v
// funtion of sorting
void swap(Node *a,Node *b);
int partition(Node a[],int low,int high);
void quicksort(Node a[],int low,int high);
// end of function
int getNode(Node a[],int key);
double shortestPath(Graph a,int s,int t,int *path,int *lenght);

int main()
{
    Graph graph=createGrpah();
    addVertex(graph,0,"S");
    addVertex(graph,1,"1");
    addVertex(graph,2,"2");
    addVertex(graph,3,"3");
    addVertex(graph,4,"4");
    addVertex(graph,5,"5");
    addVertex(graph,6,"6");
    addVertex(graph,7,"T");
    addEdges(graph,0,1,9);
    addEdges(graph,0,5,14);
    addEdges(graph,0,6,15);
    addEdges(graph,1,2,24);
    addEdges(graph,5,2,18);
    addEdges(graph,5,4,30);
    addEdges(graph,6,4,20);
    addEdges(graph,6,7,44);
    addEdges(graph,2,4,2);
    addEdges(graph,4,3,11);
    addEdges(graph,4,7,16);
    addEdges(graph,3,2,6);
    addEdges(graph,3,7,6);
    addEdges(graph,2,7,19);
    int s=0,t=7;
    int lenght,path[MAX];
    memset(path,0,sizeof(path));
    double weight=shortestPath(graph,s,t,path,&lenght);
    if(weight==INFINITE_VALUE)
        printf("No path between %d and %d\n",s,t);
    else
    {
        printf("Path between %d and %d is:  ",s,t);
        int i;
        for(i=lenght-1;i>=0;i--)
            printf("%4d",path[i]);
        printf("\nTotal weight is %.3lf\n",weight);
    }
    return 0;
}

Graph createGrpah()
{
    Graph a;
    a.vertices=make_jrb();
    a.edges=make_jrb();
    return a;
}

void addVertex(Graph a,int id,char name[])
{
    JRB node=jrb_find_int(a.vertices,id);
    if(node==NULL)
        jrb_insert_int(a.vertices,id,new_jval_s(name));
    else
        strcpy(jval_s(node->val),name);
}

void addEdges(Graph a,int v1,int v2,double weight)   //direction : v1 to v2
{
    JRB temp=make_jrb();
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)  //node v1 has no edge
        jrb_insert_int(a.edges,v1,new_jval_v(temp));
    else
        temp=(JRB)jval_v(node->val);
    jrb_insert_int(temp,v2,new_jval_d(weight));
}

double getEdgesValue(Graph a,int v1,int v2)
{
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)
        return INFINITE_VALUE;
    JRB tree=(JRB)jval_v(node->val);
    node=jrb_find_int(tree,v2);
    if(node==NULL)
        return INFINITE_VALUE;
    return jval_d(node->val);
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

int outDegree(Graph a,int v,int *ouput)    //direction out of v
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

// function of sorting
void swap(Node *a,Node *b)
{
    Node temp=*a;
    *a=*b;
    *b=temp;
}

int partition(Node a[],int low,int high)
{
    Node pivot=a[high];
    int left=low;
    int right=high-1;
    while(1)
    {
        while(left<=right && a[left].distance<=pivot.distance)
            left++;
        while(left<=right && a[right].distance>=pivot.distance)
            right--;
        if(left>=right)
            break;
        swap(&a[left],&a[right]);
        left++;
        right--;
    }
    swap(&a[left],&a[high]);
    return left;
}

void quicksort(Node a[],int low,int high)
{
    if(low<high)
    {
        int pi=partition(a,low,high);
        quicksort(a,low,pi-1);
        quicksort(a,pi+1,high);
    }
}
// end of function 

int getNode(Node a[],int key)
{
    int i;
    for(i=0;i<number_of_vertex;i++)
        if(a[i].vertex==key)
            return i;
}

double shortestPath(Graph a,int s,int t,int *path,int *lenght)
{
    int len=0;
    Node *nodeVertex=(Node*)malloc(sizeof(Node)*number_of_vertex);
    Node *nodeNewVertex=(Node*)malloc(sizeof(Node)*number_of_vertex);
    int output[MAX];
    memset(output,0,sizeof(output));
    int i;
    for(i=0;i<number_of_vertex;i++)
    {   
        nodeVertex[i].parent=-1;
        nodeVertex[i].vertex=i;
        nodeVertex[i].distance=INFINITE_VALUE;
    }
    nodeVertex[s].distance=0;
    int start=0;
    while(start!=number_of_vertex)
    {
        Node temp=nodeVertex[start];
        start++;
        nodeNewVertex[temp.vertex]=temp;
        int total=outDegree(a,temp.vertex,output);    
        for(i=0;i<total;i++)
        {
            int index=getNode(nodeVertex,output[i]);
            if(nodeVertex[index].distance>temp.distance+getEdgesValue(a,temp.vertex,nodeVertex[index].vertex))
            {
                nodeVertex[index].distance=temp.distance+getEdgesValue(a,temp.vertex,nodeVertex[index].vertex);
                nodeVertex[index].parent=temp.vertex;
            }
        }
        quicksort(nodeVertex,start,number_of_vertex-1);
    }
    int index1=t;
    path[len]=t;
    len++;
    index1=nodeNewVertex[t].parent;
    while(1)
    {
        if(nodeNewVertex[index1].vertex==-1)
            return INFINITE_VALUE;
        path[len]=nodeNewVertex[index1].vertex;
        len++;
        if(nodeNewVertex[index1].vertex==s)
            break;
        index1=nodeNewVertex[index1].parent;
    }
    *lenght=len;
    return nodeNewVertex[t].distance;
}