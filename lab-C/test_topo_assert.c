#include "topo.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void write_file(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    assert(f != NULL);
    fputs(content, f);
    fclose(f);
}

static int check_order(Graph* g, int* ord) {
    for (int u = 0; u < g->n; u++) {
        for (int k = 0; k < g->adj[u].size; k++) {
            int v = g->adj[u].to[k];
            int pos_u = -1, pos_v = -1;
            for (int i = 0; i < g->n; i++) {
                if (ord[i] == u) pos_u = i;
                if (ord[i] == v) pos_v = i;
            }
            if (pos_u >= pos_v) return 0;
        }
    }
    return 1;
}

void test_linear() {
    write_file("input.txt", "x y z\nx y\ny z\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(check_order(&g, ord));
    free(ord);
    g_free(&g);
}

void test_branching() {
    write_file("input.txt", "a b c d\na b\na c\nb d\nc d\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(check_order(&g, ord));
    free(ord);
    g_free(&g);
}

void test_empty() {
    write_file("input.txt", "\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) != 0);
}

void test_cycle() {
    write_file("input.txt", "p q r\np q\nq r\nr p\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) != 0);
    free(ord);
    g_free(&g);
}

void test_no_edges() {
    write_file("input.txt", "m n o p\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    free(ord);
    g_free(&g);
}

void test_duplicate_edges() {
    write_file("input.txt", "u v w\nu v\nu v\nv w\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(check_order(&g, ord));
    free(ord);
    g_free(&g);
}

void test_unknown_word() {
    write_file("input.txt", "a b\nx y\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) != 0);
}

void test_long_chain() {
    char buf[4096] = { 0 };
    for (int i = 0; i < 20; i++) {
        char tmp[16];
        snprintf(tmp, sizeof(tmp), "v%d ", i);
        strcat(buf, tmp);
    }
    strcat(buf, "\n");
    for (int i = 0; i < 19; i++) {
        char tmp[32];
        snprintf(tmp, sizeof(tmp), "v%d v%d\n", i, i + 1);
        strcat(buf, tmp);
    }
    write_file("input.txt", buf);
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(check_order(&g, ord));
    free(ord);
    g_free(&g);
}

void test_single_node() {
    write_file("input.txt", "only\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(ord[0] == 0);
    free(ord);
    g_free(&g);
}

void test_multiple_components() {
    write_file("input.txt", "a b c d e f\na b\nc d\ne f\n");
    Graph g;
    assert(parse_input_file("input.txt", &g) == 0);
    int* ord = malloc(g.n * sizeof(int));
    assert(topo_sort(&g, ord) == 0);
    assert(check_order(&g, ord));
    free(ord);
    g_free(&g);
}

int main() {
    test_linear();
    test_branching();
    test_empty();
    test_cycle();
    test_no_edges();
    test_duplicate_edges();
    test_unknown_word();
    test_long_chain();
    test_single_node();
    test_multiple_components();
    printf("All tests passed!\n");
    return 0;
}
