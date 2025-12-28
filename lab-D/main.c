#include "graph_coloring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 10000

int main(void) {
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    if (!in) { fprintf(stderr, "Cannot open input.txt\n"); return 1; }
    int V, K;
    if (fscanf(in, "%d %d", &V, &K) != 2) { fprintf(stderr, "Bad input header\n"); fclose(in); if (out) fclose(out); return 1; }
    int ch; while ((ch = fgetc(in)) != EOF && ch != '\n');
    Graph* g = graph_create(V);
    if (!g) { fprintf(stderr, "Memory error\n"); fclose(in); if (out) fclose(out); return 1; }
    char line[MAX_LINE];
    for (int i = 0; i < V; ++i) {
        if (!fgets(line, sizeof(line), in)) break;
        char* tok = strtok(line, " \t\r\n");
        while (tok) { int nb = atoi(tok); if (nb >= 1 && nb <= V) graph_add_edge(g, i, nb - 1); tok = strtok(NULL, " \t\r\n"); }
    }
    int* colors = (int*)malloc(sizeof(int) * V);
    int ok = graph_color(g, K, colors);
    if (!out) { fprintf(stderr, "Cannot open output.txt\n"); graph_free(g); free(colors); fclose(in); return 1; }
    if (!ok) { fprintf(out, "0\n"); }
    else { for (int i = 0; i < V; ++i) { if (i) fprintf(out, " "); fprintf(out, "%d", colors[i]); } fprintf(out, "\n"); }
    graph_free(g); free(colors); fclose(in); fclose(out);
    return 0;
}