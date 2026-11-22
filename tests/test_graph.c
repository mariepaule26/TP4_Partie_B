#include "graph0.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    Graph *g = createGraph(5);
    assert(g != NULL);
    addEdge(g, 0, 1); addEdge(g, 1, 2); addEdge(g, 2, 3); addEdge(g, 3, 4);
    int nb = welshPowell(g);
    assert(nb >= 2 && nb <= 3);
    for (int u = 0; u < g->n; ++u)
        for (int v = u + 1; v < g->n; ++v)
            if (g->A[(size_t)u * g->n + v]) assert(g->colors[u] != g->colors[v]);
    /* Relancer doit réinitialiser les couleurs et produire une coloration valide. */
    assert(welshPowell(g) == nb);
    freeGraph(g);
    puts("Tous les tests sont réussis.");
    return 0;
}
