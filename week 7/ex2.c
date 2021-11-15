#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"
#include"dllist.h"
#define max 100

typedef JRB Graph;

Graph createGraph();
void print(Graph a);
void addEdges(Graph a,int v1,int v2);
int adjacent(Graph a,int v1,int v2);
int getAdjacent(Graph a,int vertex,int *output);
void dropGraph(Graph a);
void printVertex(int v);
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
    addEdges(graph,6,7);
    print(graph);
    printf("DFS from 0 to 6: ");
    DFS(graph,0,6,printVertex);
    printf("\n");
    printf("DFS all: ");
    DFS(graph,0,-1,printVertex);
    return 0;
}

Graph createGraph()
{
    Graph a;
    a=make_jrb();
    return a;
}

void print(Graph a)
{
    JRB temp,tree,node;
    jrb_traverse(temp,a)
    {
        printf("%d:\t",jval_i(temp->key));
        tree=(JRB)jval_v(temp->val);
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
    JRB temp=make_jrb();
    JRB node=jrb_find_int(a,v1);
    if(node==NULL)
    {
        jrb_insert_int(a,v1,new_jval_v(temp));
        jrb_insert_int(temp,v2,new_jval_i(1));
    }
    else
    {
        temp=(JRB)jval_v(node->val);
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
        temp=(JRB)jval_v(node->val);
        jrb_insert_int(temp,v1,new_jval_i(1));
    }
}

int adjacent(Graph a,int v1,int v2)
{
    JRB temp=jrb_find_int(a,v1);
    if(temp==NULL)
        return 0;
    JRB node=jrb_find_int((JRB)jval_v(temp->val),v2);
    if(node==NULL)
        return 0;
    return 1;
}

int getAdjacent(Graph a,int vertex,int *output)
{
    JRB node=jrb_find_int(a,vertex);
    JRB tree=(JRB)jval_v(node->val);
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
    JRB node;
    jrb_traverse(node,a)
    {
        jrb_free_tree(jval_v(node->val));
    }
}

void printVertex(int v)
{
    printf("%5d",v);
}

void DFS(Graph a,int start,int stop,void (*func)(int))
{
    int mark[max],output[max];
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
