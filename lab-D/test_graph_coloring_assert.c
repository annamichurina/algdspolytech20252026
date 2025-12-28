#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph_coloring.h"

static int check_coloring(Graph* g, int K, int* colors, int expect_ok) {
    if (!expect_ok) return 1;
    for (int v = 0; v < g->V; ++v) {
        if (colors[v]<1 || colors[v]>K) return 0;
        for (int i = 0; i < g->deg[v]; ++i) if (colors[g->adj[v][i]] == colors[v]) return 0;
    }
    return 1;
}

int main(void) {
    Graph* g1 = graph_create(1); int c1[1]; assert(graph_color(g1, 1, c1) == 1); assert(check_coloring(g1, 1, c1, 1)); graph_free(g1);
    Graph* g2 = graph_create(2); graph_add_edge(g2, 0, 1); int c2[2]; assert(graph_color(g2, 1, c2) == 0); graph_free(g2);
    Graph* g3 = graph_create(2); graph_add_edge(g3, 0, 1); int c3[2]; assert(graph_color(g3, 2, c3) == 1); assert(check_coloring(g3, 2, c3, 1)); graph_free(g3);
    Graph* g4 = graph_create(3); graph_add_edge(g4, 0, 1); graph_add_edge(g4, 1, 2); graph_add_edge(g4, 2, 0); int c4[3]; assert(graph_color(g4, 2, c4) == 0); graph_free(g4);
    Graph* g5 = graph_create(3); graph_add_edge(g5, 0, 1); graph_add_edge(g5, 1, 2); graph_add_edge(g5, 2, 0); int c5[3]; assert(graph_color(g5, 3, c5) == 1); assert(check_coloring(g5, 3, c5, 1)); graph_free(g5);
    Graph* g6 = graph_create(5); int c6[5]; assert(graph_color(g6, 1, c6) == 1); assert(check_coloring(g6, 1, c6, 1)); graph_free(g6);
    Graph* g7 = graph_create(5); for (int i = 0; i + 1 < 5; ++i) graph_add_edge(g7, i, i + 1); int c7[5]; assert(graph_color(g7, 2, c7) == 1); assert(check_coloring(g7, 2, c7, 1)); graph_free(g7);
    Graph* g8 = graph_create(4); for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) graph_add_edge(g8, i, j); int c8[4]; assert(graph_color(g8, 3, c8) == 0); graph_free(g8);
    Graph* g9 = graph_create(4); for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) graph_add_edge(g9, i, j); int c9[4]; assert(graph_color(g9, 4, c9) == 1); assert(check_coloring(g9, 4, c9, 1)); graph_free(g9);
    Graph* g10 = graph_create(6); for (int i = 1; i < 6; ++i) graph_add_edge(g10, 0, i); int c10[6]; assert(graph_color(g10, 2, c10) == 1); assert(check_coloring(g10, 2, c10, 1)); graph_free(g10);
    Graph* g11 = graph_create(5); for (int i = 0; i < 5; ++i) graph_add_edge(g11, i, (i + 1) % 5); int c11[5]; assert(graph_color(g11, 2, c11) == 0); graph_free(g11);
    printf("All assert-based tests passed.\n");
    return 0;
}