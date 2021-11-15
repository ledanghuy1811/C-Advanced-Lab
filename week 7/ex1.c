#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"
#define max 100

typedef JRB Graph;
Graph createGraph();
void print(Graph a);
void addEdges(Graph a,int v1,int v2);
int adjacent(Graph a,int v1,int v2);
int getAdjacent(Graph a,int vertex,int *output);
void dropGraph(Graph a);

int main()
{
    Graph graph;
    graph=make_jrb();
    int output[max];
    memset(output,0,sizeof(output));
    addEdges(graph,0,1);
    addEdges(graph,1,2);
    addEdges(graph,3,4);
    addEdges(graph,2,5);
    addEdges(graph,2,6);
    print(graph);
    if(adjacent(graph,2,5))
        printf("2 and 5 are adjacent\n");
    int total=getAdjacent(graph,2,output);
    printf("Adjacent of node 2 is: ");
    int i;
    for(i=0;i<total;i++)
        printf("%d\t",output[i]);
    printf("\n");
    dropGraph(graph);
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
