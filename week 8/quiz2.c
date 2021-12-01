#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"dllist.h"
#include"jrb.h"
#include"jval.h"
#define MAX 100

typedef struct
{
    JRB edges;
    JRB vertices;
}Graph;

Graph createGrpah();
void addVertex(Graph a,int id,char name[]);
char *getVertex(Graph a,int id);
void addEdges(Graph a,int v1,int v2);   //direction : v1 to v2
int hasEdges(Graph a,int v1,int v2);
int inDegree(Graph a,int v,int *output);    //direction to v
int outDegree(Graph a,int v,int *ouput);    //direction out of v
int checkDAG(Graph a,int v,int *mark);
int DAG(Graph a);
void dropGraph(Graph a);
void topologicalSort(Graph a,int *output,int *n);

int main()
{
    Graph graph=createGrpah();
    int output[MAX],n,i;
    memset(output,0,sizeof(output));
    addVertex(graph,0,"CS102");
    addVertex(graph,1,"CS140");
    addVertex(graph,2,"CS160");
    addVertex(graph,3,"CS302");
    addVertex(graph,4,"CS311");
    addVertex(graph,5,"MATH300");
    addEdges(graph,0,1);
    addEdges(graph,0,2);
    addEdges(graph,1,3);
    addEdges(graph,5,4);
    addEdges(graph,3,4);
    if(!DAG(graph))
    {
        printf("Can not make topological sort\n");
        return 1;
    }
    topologicalSort(graph,output,&n);
    printf("Topological order:\n");
    sleep(1);
    printf("Loading 10%%\n");
    sleep(1);
    printf("Loading 50%%\n");
    sleep(1);
    printf("Loading 90%%\n");
    sleep(1);
    printf("Loading successfully. Here is result:\n");
    sleep(1);
    for(i=0;i<n;i++)
        printf("%s\n",getVertex(graph,output[i]));
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

char *getVertex(Graph a,int id)
{
    JRB node=jrb_find_int(a.vertices,id);
    if(node==NULL)  
        return NULL;
    return jval_s(node->val);
}

void addEdges(Graph a,int v1,int v2)   //direction : v1 to v2
{
    JRB temp=make_jrb();
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)      //node v1 has no edges
        jrb_insert_int(a.edges,v1,new_jval_v(temp));
    else
        temp=(JRB)jval_v(node->val);
    jrb_insert_int(temp,v2,new_jval_i(1));
}

int hasEdges(Graph a,int v1,int v2)
{
    JRB node=jrb_find_int(a.edges,v1);
    if(node==NULL)
        return 0;
    JRB tree=(JRB)jval_v(node->val);
    node=jrb_find_int(tree,v2);
    if(node==NULL)
        return 0;
    return 1;
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

int checkDAG(Graph a,int v,int *mark)
{
    if(mark[v]==1)
        return 0;
    mark[v]=1;
    JRB node=jrb_find_int(a.edges,v);
    if(node==NULL)
    {
        mark[v]=0;
        return 1;
    }
    JRB temp,tree;
    tree=(JRB)jval_v(node->val);
    jrb_traverse(temp,tree)
    {
        if(checkDAG(a,jval_i(temp->key),mark)==0)
            return 0;
    }
    mark[v]=0;
    return 1;
}

int DAG(Graph a)
{
    int mark[MAX];
    memset(mark,0,sizeof(mark));
    JRB node;
    jrb_traverse(node,a.vertices)
    {
        if(checkDAG(a,jval_i(node->key),mark)==0)
            return 0;
    }
    return 1;
}

void dropGraph(Graph a)
{
    jrb_free_tree(a.vertices);
    JRB node;
    jrb_traverse(node,a.edges)
    {
        jrb_free_tree((JRB)jval_v(node->val));
    }
    jrb_free_tree(a.edges);
}

void topologicalSort(Graph a,int *output,int *n)
{
    int index=0;
    Dllist queue=new_dllist();  
    int mark[MAX],out[MAX];
    memset(mark,0,sizeof(mark));
    memset(out,0,sizeof(out));
    JRB node;
    jrb_traverse(node,a.vertices)
    {
        mark[jval_i(node->key)]=inDegree(a,jval_i(node->key),out);
        if(mark[jval_i(node->key)]==0)
            dll_append(queue,node->key);
    }
    while(!dll_empty(queue))
    {
        Dllist temp=dll_first(queue);
        output[index]=jval_i(temp->val);
        dll_delete_node(temp);
        index++;
        node=jrb_find_int(a.edges,output[index-1]);
        if(node!=NULL)
        {
            JRB tree=(JRB)jval_v(node->val);
            JRB ptr;
            jrb_traverse(ptr,tree)
            {
                mark[jval_i(ptr->key)]--;
                if(mark[jval_i(ptr->key)]==0)
                    dll_append(queue,ptr->key);
            }
        }
    }
    *n=index;
}