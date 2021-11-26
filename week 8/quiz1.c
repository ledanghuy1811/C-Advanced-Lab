#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
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
int menu();

int main()
{
    Graph graph;
    int choice,number1,number2;
    char name[30],*string;
    int output[MAX],total;
    do
    {
        choice=menu();
        switch(choice)
        {
            case 1:
                graph=createGrpah();
                printf("Create Graph\n");
                sleep(1);
                printf("Loading 10%%\n");
                sleep(1);
                printf("Loading 50%%\n");
                sleep(1);
                printf("Loading 80%%\n");
                sleep(1);
                printf("Create successfully\n\n");
                break;
            case 2:
                printf("Enter ID and name: ");
                scanf("%d %s",&number1,name);
                addVertex(graph,number1,name);
                printf("Add vertex successfully\n\n");
                break;
            case 3:
                printf("Enter ID to ID: ");
                scanf("%d %d",&number1,&number2);
                addEdges(graph,number1,number2);
                printf("Add edges successfully\n\n");
                break;
            case 4:
                printf("Enter ID: ");
                scanf("%d",&number1);
                string=getVertex(graph,number1);
                if(string==NULL)
                    printf("Can not find vertex id %d\n\n",number1);
                else
                    printf("Vertex of id %d is %s\n\n",number1,string);
                break;
            case 5:
                printf("Enter ID and ID: ");
                scanf("%d %d",&number1,&number2);
                if(hasEdges(graph,number1,number2))
                    printf("They are edge\n\n");
                else
                    printf("They are not edge\n\n");
                break;
            case 6:
                printf("Enter ID: ");
                scanf("%d",&number1);
                total=inDegree(graph,number1,output);
                if(total==0)
                    printf("%d has no inDegree\n\n",number1);
                else
                {
                    printf("%d has %d inDgree:\t",number1,total);
                    int i;
                    for(i=0;i<total;i++)
                        printf("%d\t",output[i]);
                    printf("\n\n");
                }
                break;
            case 7:
                printf("Enter ID: ");
                scanf("%d",&number1);
                total=outDegree(graph,number1,output);
                if(total==0)
                    printf("%d has no outDegree\n\n",number1);
                else
                {
                    printf("%d has %d outDgree:\t",number1,total);
                    int i;
                    for(i=0;i<total;i++)
                        printf("%d\t",output[i]);
                    printf("\n\n");
                }
                break;
            case 8:
                printf("Check if graph is DAG:\n");
                sleep(1);
                printf("Loading 60%%\n");
                sleep(1);
                printf("Loading 90%%\n");
                sleep(1);
                if(DAG(graph)==0)
                    printf("This graph is not DAG\n\n");
                else
                    printf("This graph is DAG\n\n");
                break;
            case 9:
                printf("Thanks for using\n\n");
                dropGraph(graph);
                break;
            default:
                printf("Wrong option. Try again\n\n");
                break;
        }
    }while(choice!=9);
    return 0;
}

Graph createGrpah()
{
    Graph a;
    a.edges=make_jrb();
    a.vertices=make_jrb();
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
    JRB temp=(JRB)jval_v(node->val);
    node=jrb_find_int(temp,v2);
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
    JRB tree,temp;
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

int menu()
{
    int choice;
    printf("-------------------MENU---------------\n");
    printf("1.Create Graph\n");
    printf("2.Add vertex\n");
    printf("3.Add edges\n");
    printf("4.Get vertex\n");
    printf("5.Get edges\n");
    printf("6.Find inDegree\n");
    printf("7.Find outDegree\n");
    printf("8.Check DAG\n");
    printf("9.Drop graph and exit\n");
    printf("---------------------------------------\n\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    return choice;
}