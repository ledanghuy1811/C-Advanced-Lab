#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"
#include"dllist.h"
#define MAX 100

typedef JRB Graph;

Graph createGraph();
void printGraph(Graph a);
void addEdges(Graph a,int v1,int v2);
int adjacent(Graph a,int v1,int v2);
int getAdjacent(Graph a,int vertex,int *output);
void dropGraph(Graph a);
void printVertex(int v);
void BFS(Graph a,int start,int stop,void (*func)(int));
void DFS(Graph a,int start,int stop,void (*func)(int));

int main()
{
    Graph graph;
    graph=createGraph();
    addEdges(graph,0,1);
    addEdges(graph,0,2);
    addEdges(graph,1,2);
    addEdges(graph,1,3);
    addEdges(graph,2,4);
    addEdges(graph,2,5);
    addEdges(graph,4,5);
    addEdges(graph,1,5);
    addEdges(graph,4,6);
    addEdges(graph,4,8);
    addEdges(graph,6,7);
    printGraph(graph);
    printf("\n");
    printf("BFS from 0 to 6: ");
    BFS(graph,0,6,printVertex);
    printf("\n");
    printf("BFS all: ");
    BFS(graph,0,-1,printVertex);
    printf("\n\n");
    printf("DFS from 0 to 6: ");
    DFS(graph,0,6,printVertex);
    printf("\n");
    printf("DFS all: ");
    DFS(graph,0,-1,printVertex);
    return 0;
}

Graph createGraph()
{
    Graph temp;
    temp=make_jrb();
    return temp;
}

void printGraph(Graph a)
{
    Graph temp,tree,node;
    jrb_traverse(temp,a)
    {
        printf("%d\t",jval_i(temp->key));
        tree=(Graph)jval_v(temp->val);
        jrb_traverse(node,tree)
        {
            printf("%d\t",jval_i(node->key));
        }
        printf("\n");
    }
}

void addEdges(Graph a,int v1,int v2)
{
    // add v2 to v1
    Graph temp=make_jrb();
    Graph node=jrb_find_int(a,v1);
    if(node==NULL)
    {
        jrb_insert_int(a,v1,new_jval_v(temp));
        jrb_insert_int(temp,v2,new_jval_i(1));
    }
    else
    {
        temp=(Graph)jval_v(node->val);
        jrb_insert_int(temp,v2,new_jval_i(1));
    }
    // add v1 to v2
    temp=make_jrb();
    node=jrb_find_int(a,v2);
    if(node==NULL)
    {
        jrb_insert_int(a,v2,new_jval_v(temp));
        jrb_insert_int(temp,v1,new_jval_i(1));
    }
    else
    {
        temp=(Graph)jval_v(node->val);
        jrb_insert_int(temp,v1,new_jval_i(1));
    }
}

int adjacent(Graph a,int v1,int v2)
{
    Graph temp=jrb_find_int(a,v1);
    if(temp==NULL)
        return 0;
    Graph node=jrb_find_int((Graph)jval_v(temp->val),v2);
    if(node==NULL)
        return 0;
    return 1;
}

int getAdjacent(Graph a,int vertex,int *output)
{
    Graph node=jrb_find_int(a,vertex);
    if(node==NULL)
        return -1;
    Graph tree=(Graph)jval_v(node->val);
    int total=0;
    jrb_traverse(node,tree)
    {
        output[total]=jval_i(node->key);
        total++;
    }
    return total;
}

void dropGraph(Graph a)
{
    Graph node;
    jrb_traverse(node,a)
    {
        jrb_free_tree(jval_v(node->val));
    }
}

void printVertex(int v)
{
    printf("%5d",v);
}

void BFS(Graph a,int start,int stop,void (*func)(int))
{
    int mark[MAX],output[MAX];
    memset(mark,0,sizeof(mark));
    memset(output,0,sizeof(output));
    Dllist queue=new_dllist();
    dll_append(queue,new_jval_i(start));
    while(!dll_empty(queue))
    {
        Dllist node=dll_first(queue);
        int u=jval_i(node->val);
        dll_delete_node(node);
        if(mark[u]==0)
        {
            func(u);
            mark[u]=1;
            if(u==stop)
                return;
            int i,total;
            total=getAdjacent(a,u,output);
            for(i=0;i<total;i++)
                if(mark[output[i]]==0)
                    dll_append(queue,new_jval_i(output[i]));
        }
    }
}

void DFS(Graph a,int start,int stop,void (*func)(int))
{
    int mark[MAX],output[MAX];
    memset(mark,0,sizeof(mark));
    memset(output,0,sizeof(output));
    Dllist stack=new_dllist();
    dll_append(stack,new_jval_i(start));
    while(!dll_empty(stack))
    {
        Dllist node=dll_last(stack);
        int u=jval_i(node->val);
        dll_delete_node(node);
        if(mark[u]==0)
        {
            func(u);
            mark[u]=1;
            if(u==stop)
                return;
            int i,total;
            total=getAdjacent(a,u,output);
            for(i=0;i<total;i++)
                if(mark[output[i]]==0)
                    dll_append(stack,new_jval_i(output[i]));
        }
    }
}

