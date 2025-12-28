#include "graph_coloring.h"
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 4

Graph* graph_create(int V) {
    if (V <= 0) return NULL;
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (!g) return NULL;
    g->V = V;
    g->deg = (int*)calloc(V, sizeof(int));
    g->cap = (int*)malloc(sizeof(int) * V);
    g->adj = (int**)malloc(sizeof(int*) * V);
    if (!g->deg || !g->cap || !g->adj) { graph_free(g); return NULL; }
    for (int i = 0; i < V; ++i) {
        g->cap[i] = INIT_CAP;
        g->adj[i] = (int*)malloc(sizeof(int) * INIT_CAP);
        if (!g->adj[i]) { graph_free(g); return NULL; }
        g->deg[i] = 0;
    }
    return g;
}

void graph_free(Graph* g) {
    if (!g) return;
    if (g->deg) free(g->deg);
    if (g->cap) free(g->cap);
    if (g->adj) {
        for (int i = 0; i < g->V; ++i) if (g->adj[i]) free(g->adj[i]);
        free(g->adj);
    }
    free(g);
}

static int has_edge(Graph* g, int u, int v) {
    for (int i = 0; i < g->deg[u]; ++i) if (g->adj[u][i] == v) return 1;
    return 0;
}

void graph_add_edge(Graph* g, int u, int v) {
    if (!g || u < 0 || v < 0 || u >= g->V || v >= g->V || u == v) return;
    if (!has_edge(g, u, v)) {
        if (g->deg[u] >= g->cap[u]) {
            int newcap = g->cap[u] * 2;
            int* newarr = (int*)realloc(g->adj[u], sizeof(int) * newcap);
            if (!newarr) return;
            g->adj[u] = newarr; g->cap[u] = newcap;
        }
        g->adj[u][g->deg[u]++] = v;
    }
    if (!has_edge(g, v, u)) {
        if (g->deg[v] >= g->cap[v]) {
            int newcap = g->cap[v] * 2;
            int* newarr = (int*)realloc(g->adj[v], sizeof(int) * newcap);
            if (!newarr) return;
            g->adj[v] = newarr; g->cap[v] = newcap;
        }
        g->adj[v][g->deg[v]++] = u;
    }
}

typedef struct { int idx; int deg; } VertexOrder;

static int cmp_vertexorder(const void* a, const void* b) {
    const VertexOrder* pa = (const VertexOrder*)a, * pb = (const VertexOrder*)b;
    if (pb->deg > pa->deg) return 1;
    if (pb->deg < pa->deg) return -1;
    return 0;
}

static int try_color_rec(Graph* g, int K, int* order, int pos, int* colors) {
    if (pos == g->V) return 1;
    int v = order[pos];
    for (int c = 1; c <= K; ++c) {
        int ok = 1;
        for (int i = 0; i < g->deg[v]; ++i) if (colors[g->adj[v][i]] == c) { ok = 0; break; }
        if (ok) { colors[v] = c; if (try_color_rec(g, K, order, pos + 1, colors)) return 1; colors[v] = 0; }
    }
    return 0;
}

int graph_color(Graph* g, int K, int* colors) {
    if (!g || K <= 0 || !colors) return 0;
    VertexOrder* vo = (VertexOrder*)malloc(sizeof(VertexOrder) * g->V);
    if (!vo) return 0;
    for (int i = 0; i < g->V; ++i) { vo[i].idx = i; vo[i].deg = g->deg[i]; }
    qsort(vo, g->V, sizeof(VertexOrder), cmp_vertexorder);
    int* order = (int*)malloc(sizeof(int) * g->V);
    if (!order) { free(vo); return 0; }
    for (int i = 0; i < g->V; ++i) order[i] = vo[i].idx;
    free(vo);
    for (int i = 0; i < g->V; ++i) colors[i] = 0;
    int res = try_color_rec(g, K, order, 0, colors);
    free(order);
    return res;
}