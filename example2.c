/*parcurgerge  graf cu DFS/BFS*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;
/// utils
NODE *createNode(int v)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->data = v;
    new_node->next = NULL;
    
    return new_node;
}

GRAPH *createGraph(int vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));

    graph->visited = malloc(sizeof(int) * vertices);
    
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

void addEdge(GRAPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;

}

void insertEdge(int nr_of_vertices, int nr_of_edges, GRAPH *graph)
{
    int src, dest, i;
    
    printf("adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices-1);
    
    for (i = 0; i < nr_of_edges; i++) 
    {
        scanf("%d", &src);
        scanf("%d", &dest);
        addEdge(graph, src, dest);
    }
}
/// bfs utils
int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = createNode(data);

    if ( isEmpty(*queue) )
        *queue = new_node;
    else
    {
        NODE *temp = *queue;

        while ( temp->next )
            temp = temp->next;

        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;

    *queue = (*queue)->next;
    
    return data;
}

void printGraph(GRAPH *graph)
{
    int i;
    
    for (i = 0; i < graph->vertices; i++)
    {
        NODE *temp = graph->adjacency_lists[i];

        printf("%d: ", i);
        while ( temp )
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        
        printf("\n");
    }
}

void printQueue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}


void wipeVisitedList(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}
// parcurgeri
void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while ( temp != NULL )
    {
        int connected_vertex = temp->data;

        if ( graph->visited[connected_vertex] == 0 )
            DFS(graph, connected_vertex);
        
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while ( !isEmpty(queue) )
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while ( temp )
        {
            int adj_vertex = temp->data;

            if ( graph->visited[adj_vertex] == 0 )
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            
            temp = temp->next;
        }
    }
}

int main()
{
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;
    
    printf("cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    
    printf("cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = createGraph(nr_of_vertices);
    insertEdge(nr_of_vertices, nr_of_edges, graph);
    
    printf("de unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    
    printf("parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    wipeVisitedList(graph, nr_of_vertices);
    printf("\n");

    printf("de unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    
    printf("parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
