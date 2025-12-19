#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

typedef struct Graph Graph; 
typedef struct Vertex Vertex; 
typedef struct Edge Edge;

struct Edge {
    int label;
    void *value;

    Vertex *tail, *head;

    Edge *next;
};

struct Vertex {
    int label;
    void *value;
    Vertex *next;

    int n;
    Edge *first;
    Edge *last;
};

struct Graph {
    int n;
    Vertex *first;
    Vertex *last;
};

Graph  *Graph_alloc();
void    Graph_free();
void    Graph_insertVertex(Graph *g, void *value);
void    Graph_insertEdge(Graph *g, int label1, int label2, void *value);
void    Graph_print(Graph *g);
Vertex *Graph_find(Graph *g, int label);
Vertex *Graph_findByValue(Graph *g, void *value, int (*cmp)(void*,void*));
void   *Graph_removeVertex(Graph *g, int label);
void   *Graph_removeEdge(Graph *g, int label1, int label2);

#endif
