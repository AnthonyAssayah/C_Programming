#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <stdlib.h>

typedef struct GRAPH_NODE_ *node_ptr;;

typedef struct edge_ {
    int weight;
    int destination;
    struct edge_ *next;
} edge, *edge_ptr;


typedef struct GRAPH_NODE_ {
    int node_num;
    edge_ptr edges_out;
    int num_of_edges;
    struct GRAPH_NODE_ *next;
} node, *node_ptr;


void build_graph_cmd(node_ptr *first, int len);
void insert_node_cmd(node_ptr *first, int source) ;
void delete_node_cmd(node_ptr *first, int id);
void delete_graph_cmd(node_ptr* first);
int shortest_path_cmd(node_ptr *first, int source, int destination);
void TSP_cmd(node_ptr *first, int len, int arr[]);
void create_node(node_ptr *first, int id);
void add_edge(node_ptr *first, int source, int destination, int w);
void swap(int *x, int *y);
void rout(node_ptr *first, int *a, int start, int end);



char A(node_ptr *first, char input);
char B(node_ptr *first, char input);
char D(node_ptr *first, char input);
char T(node_ptr *first, char input);
char S(node_ptr *first, char input);
#endif
