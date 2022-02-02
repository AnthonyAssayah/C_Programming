#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Queue struct decleration
typedef struct Queue
{
    int head, get_last, size, max_size, *Q;
} Queue;

//check if the my_DS is empty
int empty(struct Queue *q)
{
    return (q->size) == 0;
}

// checks if the my_DS is full
int full(struct Queue *q)
{
    return (q->size == q->max_size);
}

// create a Queue
struct Queue *create_queue(int size)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    
    q->max_size = size;
    q->head = 0;
    q->size = 0;
    q->get_last = q->max_size - 1;
    q->Q = (int *)malloc(q->max_size * sizeof(int));
    
    return q;
}

// return the head of the Queue
int head(struct Queue *q)
{
    if (empty(q))
    {
        return INT_MIN;
    }
    else
    {
        return q->Q[q->head];
    }
}

// returns the last element of the Queue
int get_last(struct Queue *q)
{
    if (empty(q))
    {
        return INT_MIN;
    }
    else
    {
        return q->Q[q->get_last];
    }
}

// add an element to the Queue
void push_back(struct Queue *q, int node_id)
{
    
    if (full(q))
    {
        return;
    }
    
    q->get_last = (q->get_last + 1) % q->max_size; 
    q->Q[q->get_last] = node_id;
    q->size++;
}

// remove an element from the Queue
int pop_front(struct Queue *q)
{

    if (full(q))
    {
        return INT_MIN;
    }
    
    int firstNode = q->Q[q->head];
    
    q->head = (q->head + 1) % q->max_size;
    q->size--;
    
    return firstNode;
}