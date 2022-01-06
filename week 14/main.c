#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jval.h"
#define WALK_WAY 50
#define INFINITE_VALUE 1000000
#define MAX 100

int number_of_vertex;

typedef JRB Graph;

typedef struct
{
    int vertex;
    int time;
    int parent;
}Node;

Graph createGraph();
void addEdges(Graph a,int v1,int v2,int time);
void loadFile(Graph a,FILE *f);
int getAdjacent(Graph a,int v1,int v2);
void printGraph(Graph a);
void castleWalking(Graph a);
void castleOfMostWay(Graph a);
// funtion of sorting
void swap(Node *a,Node *b);
int partition(Node a[],int low,int high);
void quicksort(Node a[],int low,int high);
// end of function
int outDegree(Graph a,int vertex,int *output);
int getNode(Node a[],int key);
int shortestPath(Graph a,int s,int t,int *path,int *lenght);
int shortestWalkingPath(Graph a,int s,int t,int *path,int *lenght);

int main()
{
    Graph CastleWay=createGraph();
    FILE *f;
    int choice;
    int s,t,i;
    int path[MAX];
    memset(path,0,sizeof(path));
    int len,lenght;
    do
    {
        printf("------------------MENU-----------------\n");
        printf("1.Load file\n");
        printf("2.Print list of castle\n");
        printf("3.Print castle that can only walk to it\n");
        printf("4.Print castle that have the most way can come to\n");
        printf("5.Find the shortest path\n");
        printf("6.Find the shortest path(walking)\n");
        printf("7.Exit\n");
        printf("------------------------------------------\n\n");
        printf("Your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Load file\n");
                printf("Successfully. Here is matrix:\n");
                f=fopen("dothi.txt","r");
                loadFile(CastleWay,f);
                fclose(f);
                printf("\n");
                break;
            case 2:
                printf("List of castle:\n");
                printGraph(CastleWay);
                printf("\n");
                break;
            case 3:
                printf("List of castle than only walk to is: ");
                castleWalking(CastleWay);
                printf("\n\n");
                break;
            case 4:
                printf("Castle that have the most way through is: ");
                castleOfMostWay(CastleWay);
                printf("\n\n");
                break;
            case 5:
                printf("Enter castle s-t: ");
                scanf("%d-%d",&s,&t);
                lenght=shortestPath(CastleWay,s-1,t-1,path,&len);
                printf("Lenght of way is: %d\n",lenght);
                printf("Way is: ");
                for(i=len-1;i>=0;i--)
                    printf("%d\t",path[i]+1);
                printf("\n");
                break;
            case 6:
                printf("Enter castle s-t: ");
                scanf("%d-%d",&s,&t);
                lenght=shortestWalkingPath(CastleWay,s-1,t-1,path,&len);
                    if(lenght==INFINITE_VALUE)
                    {
                        printf("ROUTE NOT FOUND\n\n");
                        break;
                    }
                printf("Lenght of walking way is: %d\n",lenght);
                printf("Way is: ");
                for(i=len-1;i>=0;i--)
                    printf("%d\t",path[i]+1);
                printf("\n");
                break;
            case 7:
                printf("Thanks for using\n\n");
                break;
            default:
                printf("Wrong option\n\n");
                break;
        }
    }while(choice!=7);
    return 0;
}

Graph createGraph()
{
    Graph temp;
    temp=make_jrb();
    return temp;
}

void addEdges(Graph a,int v1,int v2,int time)
{
    // add v2 to v1
    Graph temp=make_jrb();
    Graph node=jrb_find_int(a,v1);
    if(node==NULL)
    {
        jrb_insert_int(a,v1,new_jval_v(temp));
        jrb_insert_int(temp,v2,new_jval_i(time));
    }
    else
    {
        temp=(Graph)jval_v(node->val);
        jrb_insert_int(temp,v2,new_jval_i(time));
    }
    // add v1 to v2
    temp=make_jrb();
    node=jrb_find_int(a,v2);
    if(node==NULL)
    {
        jrb_insert_int(a,v2,new_jval_v(temp));
        jrb_insert_int(temp,v1,new_jval_i(time));
    }
    else
    {
        temp=(Graph)jval_v(node->val);
        jrb_insert_int(temp,v1,new_jval_i(time));
    }
}

void loadFile(Graph a,FILE *f)
{
    int id1,id2,time;
    int n,m;
    fscanf(f,"%d%d",&n,&m);
    number_of_vertex=n;
    int matrix[n][n];
    memset(matrix,0,sizeof(matrix));
    while(fscanf(f,"%d%d%d",&id1,&id2,&time)==3)
    {
        addEdges(a,id1-1,id2-1,time);
        matrix[id1-1][id2-1]=time;
        matrix[id2-1][id1-1]=time;
    }
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d\t",matrix[i][j]);
        printf("\n");
    }
}

int getAdjacent(Graph a,int v1,int v2)
{
    Graph temp=jrb_find_int(a,v1);
    if(temp==NULL)
        return INFINITE_VALUE;
    Graph node=jrb_find_int((Graph)jval_v(temp->val),v2);
    if(node==NULL)
        return INFINITE_VALUE;
    return jval_i(node->val);
}

void printGraph(Graph a)
{
    Graph temp,tree,node;
    jrb_traverse(temp,a)
    {
        printf("Castle %d:\t",jval_i(temp->key)+1);
        tree=(Graph)jval_v(temp->val);
        jrb_traverse(node,tree)
        {
            printf("%d\t",jval_i(node->key)+1);
        }
        printf("\n");
    }
}

void castleWalking(Graph a)
{
    Graph tree,node,root;
    jrb_traverse(tree,a)
    {
        int min=INFINITE_VALUE;
        root=(Graph)jval_v(tree->val);
        jrb_traverse(node,root)
        {
            if(min>jval_i(node->val))
                min=jval_i(node->val);
        }
        if(min>=WALK_WAY)
            printf("%d\t",jval_i(tree->key)+1);
    }
}

void castleOfMostWay(Graph a)
{
    Graph tree,node,root;
    int max=0;
    jrb_traverse(tree,a)
    {
        int cout=0;
        root=(Graph)jval_v(tree->val);
        jrb_traverse(node,root)
        {
           cout++;
        }
        if(max<cout)
            max=cout;
    }
    jrb_traverse(tree,a)
    {
        int cout=0;
        root=(Graph)jval_v(tree->val);
        jrb_traverse(node,root)
        {
           cout++;
        }
        if(max==cout)
            printf("%d\t",jval_i(tree->key)+1);
    }
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
        while(left<=right && a[left].time<=pivot.time)
            left++;
        while(left<=right && a[right].time>=pivot.time)
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

int outDegree(Graph a,int vertex,int *output)
{
    Graph tree,node,root;
    tree=jrb_find_int(a,vertex);
    if(node==NULL)
        return 0;
    root=(Graph)jval_v(tree->val);
    int total=0;
    jrb_traverse(node,root)
    {
        output[total]=jval_i(node->key);
        total++;
    }
    return total;
}

int getNode(Node a[],int key)
{
    int i;
    for(i=0;i<number_of_vertex;i++)
        if(a[i].vertex==key)
            return i;
}

int shortestPath(Graph a,int s,int t,int *path,int *lenght)
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
        nodeVertex[i].time=INFINITE_VALUE;
    }
    nodeVertex[s].time=0;
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
            if(nodeVertex[index].time>temp.time+getAdjacent(a,temp.vertex,nodeVertex[index].vertex))
            {
                nodeVertex[index].time=temp.time+getAdjacent(a,temp.vertex,nodeVertex[index].vertex);
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
    return nodeNewVertex[t].time;
}

int shortestWalkingPath(Graph a,int s,int t,int *path,int *lenght)
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
        nodeVertex[i].time=INFINITE_VALUE;
    }
    nodeVertex[s].time=0;
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
            int weight=getAdjacent(a,temp.vertex,nodeVertex[index].vertex);
            if(weight<WALK_WAY)
                weight=INFINITE_VALUE;
            if(nodeVertex[index].time>temp.time+weight)
            {
                nodeVertex[index].time=temp.time+weight;
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
    return nodeNewVertex[t].time;
}