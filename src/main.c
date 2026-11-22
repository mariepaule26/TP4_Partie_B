#include "graph0.h"
#include <stdio.h>

int main(void) {
    Graph *g = createGraph(5);
    if (!g) { fputs("Erreur : allocation mémoire impossible.\n", stderr); return 1; }
    addEdge(g, 0, 1); addEdge(g, 0, 2); addEdge(g, 1, 2);
    addEdge(g, 1, 3); addEdge(g, 2, 4); addEdge(g, 3, 4);
    puts("Graphe de démonstration");
    displayAdjacency(g);
    int nb = welshPowell(g);
    if (nb < 0) { freeGraph(g); return 1; }
    displayDegres(g);
    displayColoring(g);
    if (!dotExport(g, "resultats/graphe_demo.dot")) fprintf(stderr, "Impossible d'écrire le fichier DOT.\n");
    freeGraph(g);
    return 0;
}
