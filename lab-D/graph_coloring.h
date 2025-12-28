#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

typedef struct Graph {
    int V;
    int* deg;
    int** adj;
    int* cap;
} Graph;

Graph* graph_create(int V);
void graph_free(Graph* g);
void graph_add_edge(Graph* g, int u, int v);
int graph_color(Graph* g, int K, int* colors);

#endif