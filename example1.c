/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int num_of_vertices;
    int *visited;
    struct Node **head;
} GRAPH;

typedef struct Stack {
    int top;
    int capacity;
    int *arr;
} STACK;

NODE *createNode(int data)
{
    NODE *new_node = malloc(sizeof(NODE));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void addEdge(GRAPH *graph,int src,int dest)
{
    NODE *new_node = createNode(dest);

    new_node->next = graph->head[src];
    graph->head[src] = new_node;

    new_node = createNode(src);
    new_node->next = graph->head[dest];
    graph->head[dest] = new_node;
}

GRAPH *createGraph(int num_of_vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));

    graph->num_of_vertices = num_of_vertices;
    graph->head = malloc(num_of_vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * num_of_vertices);

    for (int i = 0; i < num_of_vertices ; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

STACK *createStack(int capacity)
{
    STACK *stack = malloc(sizeof(STACK));
    stack->arr = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
                 
    return stack;
}

void push(int data, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->arr[stack->top] = data;
}

void DFS(GRAPH *graph, STACK *stack, int v_nr)
{
    NODE *current = graph->head[v_nr];
//    NODE *aux = adj_list;
    graph->visited[v_nr] = 1;
//    printf("%d ", v_nr);
//    push(v_nr, stack);

    while (current != NULL)
    {
        int con_ver = current->data;

        if ( graph->visited[con_ver] == 0 )
            DFS(graph, stack, con_ver);
         current = current->next;
    }
}

void insertEdges(GRAPH *graph, int edg_nr, int num_of_vertices)
{
    int src,dest,i;
    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, num_of_vertices-1);

    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipeVisited(GRAPH *graph, int num_of_vertices)
{
    for (int i = 0; i < num_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

int canBe(GRAPH *graph, int num_of_vertices, int src, int dest) {
    STACK *stack = createStack(2 * num_of_vertices);
    int can_be = 0;
    
    DFS(graph, stack, src); // Căutăm un drum de la src la dest

    // Dacă dest a fost vizitat în timpul căutării DFS de la src, atunci există un drum între src și dest
    if (graph->visited[dest] == 1)
        can_be = 1;

    free(stack->arr);
    free(stack);

    return can_be;
}

int main()
{
    int num_of_vertices;
    int edg_nr;
    int src, dest;
    
    printf("cate noduri are graful? ");
    scanf("%d", &num_of_vertices);
    
    printf("cate muchii are graful? ");
    scanf("%d", &edg_nr);
    
    GRAPH *graph = createGraph(num_of_vertices);

    insertEdges(graph, edg_nr, num_of_vertices);

    printf("intre care doua restaurante se cauta drum? ");
    scanf("%d%d", &src, &dest);

    if( canBe(graph, num_of_vertices, src, dest) )
        printf("exista drum!");
    else
        printf("nu exista drum!");

    return 0;
}