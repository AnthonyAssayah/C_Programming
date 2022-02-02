#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "Queue.c"

// length of TSP
static int TSP_lenght = INT_MAX;
// the amount of nodes in the graph
static int size = 0;
// the id of the node with the maximum id in the graph
int maximum = 0;

// creates a graph
void build_graph_cmd(node_ptr *first, int len)
{

    if (*first == NULL)
    {

        node_ptr *temp = (node_ptr *)malloc(sizeof(node_ptr));

        if (temp == NULL)
        { // check if allocation failed

            printf("Error: problem with the memory allocation");
            return; // break if no memory was allocated
        }

        *first = *temp;
    }

    for (int i = 0; i < len; i++)
    {

        create_node(&(*first), i);
    }
}

void insert_node_cmd(node_ptr *first, int id)
{

    node_ptr temp = *first;
    edge_ptr *edges_out_ptr = (edge_ptr *)malloc(sizeof(struct edge_));

    if (edges_out_ptr == NULL)
    { // check if allocation failed

        printf("Error: problem with the memory allocation");
        return; // break if no memory was allocated
    }
    // if there arent any nodes in the graph
    if (size == 0)
    {
        // create the first node
        create_node(&temp, id);
        *edges_out_ptr = temp->edges_out;
        *edges_out_ptr = (edge_ptr)malloc(sizeof(edge));
        temp->edges_out = *edges_out_ptr;
        temp->edges_out->next = NULL;
        temp->num_of_edges += 1;
    }
    else
    {
        // else make a node and connect it to the last one
        int counter = 0;
        int bool = 0;

        while (counter < size)
        {

            if (temp->node_num != id)
            {

                if (size == 1)
                {

                    break;
                }
                else
                {

                    if (temp->next == NULL)
                    {

                        create_node(&temp, id);
                        temp = temp->next;
                        break;
                    }
                    else
                    {

                        temp = temp->next;
                        counter += 1;
                    }
                }
            }
            else if (temp->node_num == id)
            {

                bool = 1;
                break;
            }
        }

        if (bool == 1)
        {
            // free all the edges
            while (temp->num_of_edges > 0)
            {

                temp->num_of_edges -= 1;
                edge_ptr next = temp->edges_out->next;
                free(temp->edges_out);
                temp->edges_out = next;
            }
        }
        // free the edges_out pointer
        free(edges_out_ptr);
    }
}

// deletes the node with the id 'id'
void delete_node_cmd(node_ptr *first, int id)
{
    node_ptr temp = *first;
    edge_ptr edges_out_ptr;

    if (temp == NULL)
    {

        return;
    }
    // if the node is the head of the list (the first node)
    if (temp->node_num == id)
    {

        // iterate over the edges of the node
        while (temp->num_of_edges > 0)
        {

            // free the memory of the edge
            edge_ptr next_e = temp->edges_out->next;
            free(temp->edges_out);
            temp->edges_out = next_e;
            temp->num_of_edges -= 1;
        }
        node_ptr next_first = (*first)->next;
        //        
        free(*first);
        (*first) = next_first;
        size -= 1;
    }
    else
    {
        // finding the previous node
        node_ptr prev;

        while (temp->node_num != id)
        {

            prev = temp;
            temp = temp->next;
        }

        edges_out_ptr = temp->edges_out;
        // removing the node's edges (only the edges that go)
        while (temp->num_of_edges > 0)
        {

            edge_ptr next_edge = edges_out_ptr->next;
            free(edges_out_ptr);

            if (next_edge == NULL)
            {

                free(next_edge);
                temp->edges_out = NULL;
                temp->num_of_edges -= 1;
            }
            else
            {

                edges_out_ptr = next_edge;
                temp->num_of_edges -= 1;
                temp->edges_out = next_edge;
            }
        }

        node_ptr next_node = temp->next;
        prev->next = next_node;
        free(temp);
        size -= 1;
    }

    temp = *first;
    edges_out_ptr = temp->edges_out;

    // remove edges out:
    while (temp != NULL)
    {

        while (edges_out_ptr != NULL)
        {
            // if there are no edges in the node
            if ((temp)->num_of_edges == 0)
            {

                break;
            }
            // if the node has only one edge
            else if ((temp)->num_of_edges == 1)
            {

                if (edges_out_ptr->destination == id)
                {

                    free(edges_out_ptr);
                    temp->num_of_edges -= 1;
                    temp->edges_out = NULL;
                }
                break;
            }
            // if the node has more than one edge
            else
            {
                // if p is the first node in the list
                if (edges_out_ptr->destination == id && edges_out_ptr->next != NULL)
                {

                    edge_ptr cur = edges_out_ptr->next;
                    free(temp->edges_out);
                    temp->edges_out = cur;
                    temp->num_of_edges--;
                    break;
                }
                else if (edges_out_ptr->next != NULL && edges_out_ptr->next->destination == id)
                {

                    if (edges_out_ptr->next->next == NULL)
                    {

                        free(edges_out_ptr->next);
                        temp->num_of_edges -= 1;
                        edges_out_ptr->next = NULL;
                    }
                    else
                    {

                        edge_ptr cur = edges_out_ptr->next->next;
                        free(edges_out_ptr->next);
                        edges_out_ptr->next = cur;
                        temp->num_of_edges -= 1;
                    }

                    break;
                }
                else
                {

                    edges_out_ptr = edges_out_ptr->next;
                }
            }
        }

        temp = (temp)->next;

        if (temp != NULL)
        {

            edges_out_ptr = (temp)->edges_out;
        }
    }
}

// a function to delete the graph
void delete_graph_cmd(node_ptr *first)
{

    node_ptr temp = *first;
    node_ptr next_node;

    while (size > 0)
    {

        edge_ptr edges_out_ptr = temp->edges_out;
        next_node = (temp)->next;

        while (temp->num_of_edges > 0)
        {

            edge_ptr next_edge = edges_out_ptr->next;

            if (next_edge == NULL)
            {

                free(edges_out_ptr);
                temp->num_of_edges -= 1;
            }
            else
            {

                free(edges_out_ptr);
                edges_out_ptr = next_edge;
                temp->num_of_edges -= 1;
            }
        }
        if (next_node == NULL)
        {

            size -= 1;
        }
        else
        {

            next_node = temp->next;
            // free the node
            free(temp);
            temp = next_node;
            // set the pointer to the next node
            *first = temp;
            size -= 1;
        }
    }

    free(temp);
}

// shortest path function using dijkstra
int shortest_path_cmd(node_ptr *first, int source, int dest)
{
    // an array that holds the weight of the nodes (instead of making it a field in the node struct)
    int dist[maximum + 1];
    // an array that holds the nodes which had been already visited
    int visited[maximum + 1];

    for (int i = 0; i < maximum + 1; i++)
    {

        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[source] = 0;
    struct Queue *q = create_queue(size);
    node_ptr temp = (*first);
    push_back(q, source);
    edge_ptr edge;
    int len;

    while (!empty(q))
    {

        int curNode = pop_front(q);

        if (visited[curNode] == 0)
        {

            if (temp->node_num == curNode)
            {

                edge = temp->edges_out;
            }
            else
            {

                while (temp->node_num != curNode)
                {

                    if (temp->next != NULL)
                    {

                        temp = (temp)->next;
                        edge = temp->edges_out;
                    }
                    else
                    {

                        edge = NULL;
                        break;
                    }
                }
            }

            while (edge != NULL)
            {

                // len = weight of the node + weight of the added edge
                len = edge->weight + dist[curNode];
                int curLen = dist[edge->destination];

                if (len < curLen)
                {

                    dist[edge->destination] = len;
                    push_back(q, edge->destination);
                }

                edge = edge->next;
            }
            // remporary pointer to the first node of the list.
            temp = *first;
        }

        visited[curNode] = 1;
    }
    // free the queue
    free(q->Q);
    free(q);

    if (visited[dest] == 0)
    {
        // if the destination wasnt included in the path, return infinity as the distance
        return INT_MAX;
    }
    else
    {
        // else return the actual distance
        return dist[dest];
    }
}

void TSP_cmd(node_ptr *first, int len, int arr[])
{

    node_ptr temp = *first;
    TSP_lenght = INT_MAX;

    rout(&temp, arr, 0, len - 1);

    if (TSP_lenght == INT_MAX)
    {

        TSP_lenght = -1;
    }

    printf("TSP shortest path: %d ", TSP_lenght);
    TSP_lenght = INT_MAX;
}

void create_node(node_ptr *first, int id)
{

    if (maximum < id)
    {

        maximum = id;
    }

    node_ptr n = (node_ptr)malloc(sizeof(struct GRAPH_NODE_));

    if (n == NULL)
    { // if there is no place in memory to allocate

        printf("Error: problem with the memory allocation");
        exit(1);
    }
    // reset the node
    n->node_num = id;
    n->edges_out = NULL;
    n->next = NULL;
    n->num_of_edges = 0;

    if (size == 0)
    {

        *first = n;
        size += 1;
    }
    else
    {

        node_ptr temp = *first;

        while (temp->next != NULL)
        {

            temp = temp->next;
        }

        temp->next = n;
        size += 1;
    }
}
// function for adding an edge to the graph
void add_edge(node_ptr *first, int source, int dest, int w)
{

    node_ptr temp = *first;
    edge_ptr edges_out_ptr;

    if (temp->num_of_edges > 0)
    {

        while (temp->node_num != source)
        {

            temp = temp->next;
        }
    }

    edges_out_ptr = (temp->edges_out);
    int boo = 0;

    if (edges_out_ptr != NULL)
    {

        while (edges_out_ptr->next != NULL)
        {

            edges_out_ptr = edges_out_ptr->next;
        }

        edges_out_ptr->next = (edge_ptr)malloc(sizeof(struct edge_));
        edges_out_ptr = edges_out_ptr->next;
        boo = 1;
       
    }

    if (boo == 0)
    {

        edges_out_ptr = (edge_ptr)malloc(sizeof(edge));
        temp->edges_out = edges_out_ptr;
       
    }

    edges_out_ptr->destination = dest;
    edges_out_ptr->weight = w;
    edges_out_ptr->next = NULL;
    temp->num_of_edges++;

}

void swap(int *x, int *y)
{

    int temp = *x;
    *x = *y;
    *y = temp;
}

void rout(node_ptr *first, int *a, int start, int end)
{

    if (start == end)
    {

        int sum = 0;
        int j = 1;

        for (int i = 0; i <= end; ++i)
        {

            if (j <= end)
            {

                int **edges_out_ptr = &a;
                int s = *(i + *edges_out_ptr);
                int d = (*(j + *edges_out_ptr));
                int temp = shortest_path_cmd(first, s, d);

                if (temp == INT_MAX)
                {

                    sum = INT_MAX;
                    return;
                }
                else
                {

                    sum = sum + temp;
                    j += 1;
                }
            }
        }
        if (sum < TSP_lenght)
        {

            TSP_lenght = sum;
        }
    }
    else
    {

        for (int i = start; i <= end; i++)
        {

            swap((a + start), (a + i));
            rout(first, a, start + 1, end);
            swap((a + start), (a + i)); // backtrack
        }
    }
}


int main(void)
{

    node_ptr head = (node *)malloc(sizeof(node));

    if (head == NULL)
    { // if there is no place in memory to allocate

        printf("Error: problem with the memory allocation");
        return 1;
    }

    node_ptr first = head;

    char input = 0;
    scanf("%c", &input);

    while (1)
    {
        switch (input) {
        
            case 'A':

                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }
                if (size != 0)
                {

                    delete_graph_cmd(&first);
                    head = (node *)malloc(sizeof(node));
                    first = head;
                    input = A(&first, input);
                }
                else
                {

                    input = A(&first, input);
                }
                break;
           
           case 'B':
                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }

                if (isdigit(input))
                {

                    input = B(&first, input);
                }
            
                break;
            
            case 'D':
                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }

                if (isdigit(input))
                {

                    input = D(&first, input);
                }
                break;
            
            case 'S':

                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }

                if (isdigit(input))
                {

                    input = S(&first, input);
                }

                if (input != ' ')
                {

                    printf("\n");
                }
                break;

            case 'T':

                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }

                if (isdigit(input))
                {

                    input = T(&first, input);
                }
                if (input != ' ')
                {

                    printf("\n");
                }
                break;
            
            default:
                delete_graph_cmd(&first);
                free(head);
                return 0;
            }
            
        }

    return 0;
}

char A(node_ptr *first, char input)
{

    if (input == ' ')
    {

        scanf("%c", &input);
    }

    if (isdigit(input))
    {

        build_graph_cmd(&(*first), input - '0');
    }

    scanf("%c", &input);

    if (input == ' ')
    {

        scanf("%c", &input);
    }

    if (input == 'n')
    {

        while (input < 'A' || input > 'Z')
        { // while we don't get an upper char

            if (input == 'n')
            {

                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }

                int source = 0;
                int destination = 0;
                int w = 0;

                if (isdigit(input))
                {

                    source = input - '0';
                }

                scanf("%c", &input);

                if (input == ' ')
                {

                    scanf("%c", &input);
                }
                while (input != 'n' && (input < 'A' || input > 'Z'))
                {

                    if (isdigit(input))
                    {

                        destination = input - '0';
                    }

                    scanf("%c", &input);

                    if (input == ' ')
                    {

                        scanf("%c", &input);
                    }
                    if (isdigit(input))
                    {

                        w = input - '0';
                    }

                    add_edge(first, source, destination, w);
                    scanf("%c", &input);

                    if (input == ' ')
                    {

                        scanf("%c", &input);
                    }
                }
            }
        }
    }
    return input;
}

char B(node_ptr *first, char input)
{

    int source = input - '0';
    int destination = 0;
    int w = 0;

    insert_node_cmd(first, source); // inserting the node to the graph
    scanf("%c", &input);

    // inserting the edges
    while (input < 'A' || input > 'Z')
    { // while we don't get an upper char

        destination = 0;
        w = 0;

        if (input == ' ')
        {

            scanf("%c", &input);
        }
        if (isdigit(input))
        {

            destination = input - '0';
        }

        scanf("%c", &input);

        if (input == ' ')
        {

            scanf("%c", &input);
        }
        if (isdigit(input))
        {

            w = input - '0';
        }

        add_edge(first, source, destination, w);
        scanf("%c", &input);

        if (input == ' ')
        {

            scanf("%c", &input);
        }
    }

    return input;
}

char D(node_ptr *first, char input)
{

    delete_node_cmd(&(*first), input - '0');
    scanf("%c", &input);

    if (input == ' ')
    {

        scanf("%c", &input);
    }

    return input;
}

char T(node_ptr *first, char input)
{

    int len = input - '0';
    int counter = 0;
    int arr[len];

    while (counter < len)
    {

        scanf("%c", &input);

        if (input == ' ')
        {

            scanf("%c", &input);
        }

        if (isdigit(input))
        {

            arr[counter] = input - '0';
        }

        counter += 1;
    }

    TSP_cmd(first, len, arr);
    scanf("%c", &input);

    if (input == ' ')
    {

        scanf("%c", &input);
    }

    return input;
}

char S(node_ptr *first, char input)
{

    int source = input - '0';
    int destination = 0;
    scanf("%c", &input);

    if (input == ' ')
    {

        scanf("%c", &input);
    }
    if (isdigit(input))
    {

        destination = input - '0';
    }

    int len = shortest_path_cmd(first, source, destination);
    printf("Dijsktra shortest path: %d ", len);

    scanf("%c", &input);

    if (input == ' ')
    {

        scanf("%c", &input);
    }

    return input;
}
