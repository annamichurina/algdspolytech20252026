#include "topo.h"
#include <stdlib.h>

int main(void) {
    const char* in = "input.txt";
    const char* out = "output.txt";
    Graph g;
    if (parse_input_file(in, &g) != 0) {
        write_output_err(out);
        return 1;
    }
    int* order = (int*)malloc(g.n * sizeof(int));
    if (!order) { g_free(&g); write_output_err(out); return 2; }
    if (topo_sort(&g, order) == 0)
        write_output_ok(out, &g, order);
    else
        write_output_err(out);
    free(order);
    g_free(&g);
    return 0;
}
