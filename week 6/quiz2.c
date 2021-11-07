#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"jval.h"
#include"jrb.h"
#define max 100

typedef JRB Graph;

int menu();
Graph createGraph();
void print(Graph a);
void addEdges(Graph a,int v1,int v2);
int adjacent(Graph a,int v1,int v2);
int getAdjacent(Graph a,int vertex,int *output);
void dropGraph(Graph a);

int main()
{
    Graph graph;
    int choice,*output;
    int edge1,edge2;
    do
    {
        choice=menu();
        switch(choice)
        {
            case 1:
                printf("Creat graph:\n");
                graph=createGraph();
                printf("Loading 10%%\t");
                sleep(1);
                printf("50%%\t");
                sleep(1);
                printf("80%%\t");
                sleep(1);
                printf("100%%\n");
                output=(int*)malloc(sizeof(int)*max);
                memset(output,0,sizeof(output)*max);
                printf("Creat successfully\n\n");
                break;
            case 2:
                printf("Enter edge-edge: ");
                scanf("%d-%d",&edge1,&edge2);
                addEdges(graph,edge1,edge2);
                printf("Add successfully\n\n");
                break;
            case 3:
                printf("List of graph:\n");
                print(graph);
                printf("\n");
                break;
            case 4:
                printf("Enter edge-edge: ");
                scanf("%d-%d",&edge1,&edge2);
                int check=adjacent(graph,edge1,edge2);
                if(check)
                    printf("%d and %d are addjacent\n\n",edge1,edge2);
                else
                    printf("%d and %d are not adjacent\n\n",edge1,edge2);
                break;
            case 5:
                printf("Enter vertex: ");
                scanf("%d",&edge1);
                int total=getAdjacent(graph,edge1,output);
                if(total==0)
                    printf("%d has no adjacent\n\n",edge1);
                else
                {
                    printf("Adjacent of %d are: ",edge1);
                    int i;
                    for(i=0;i<total;i++)
                        printf("%d\t",output[i]);
                    printf("\n");
                }
                break;
            case 6:
                printf("Thanks for using\n\n");
                dropGraph(graph);
                break;
            default:
                printf("Wrong option, try again\n\n");
                break;
        }
    }while(choice!=6);  
    return 0;
}

int menu()
{
    int chocie;
    printf("--------------MENU------------\n");
    printf("1. Create graph\n");
    printf("2. Add edges\n");
    printf("3. Print the graph by matrix\n");
    printf("4. Check adjacent\n");
    printf("5. Find adjacent\n");
    printf("6. Exit and drop graph\n");
    printf("-------------------------------\n\n");
    printf("Your choice: ");
    scanf("%d",&chocie);
    return chocie;
}

Graph createGraph()
{
    Graph temp;
    temp=make_jrb();
    return temp;
}

void print(Graph a)
{
    Graph temp,tree,node;
    jrb_traverse(temp,a)
    {
        printf("%d:\t",jval_i(temp->key));
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
        return 0;
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
        jrb_free_tree((Graph)jval_v(node->val));
    }
    jrb_free_tree(a);
}
