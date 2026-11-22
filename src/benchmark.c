#include "graph0.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned int state = 123456789u;
static unsigned int nextRandom(void) { state ^= state << 13; state ^= state >> 17; state ^= state << 5; return state; }
static double elapsed(clock_t a, clock_t b) { return (double)(b-a) / CLOCKS_PER_SEC; }

int main(int argc, char **argv) {
    const int sizes[] = {10, 100, 1000, 3000, 5000, 10000};
    const double p = 0.02;
    const char *out = argc > 1 ? argv[1] : "resultats/temps.csv";
    FILE *f = fopen(out, "w");
    if (!f) { perror(out); return 1; }
    fprintf(f, "n,probabilite,aretes,temps_secondes,couleurs\n");
    for (size_t k = 0; k < sizeof sizes / sizeof sizes[0]; ++k) {
        int n = sizes[k];
        Graph *g = createGraph(n);
        if (!g) { fprintf(stderr, "Allocation impossible pour n=%d\n", n); fclose(f); return 2; }
        long long edges = 0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j)
            if ((double)(nextRandom() / (double)0xFFFFFFFFu) < p) { addEdge(g, i, j); ++edges; }
        clock_t start = clock();
        int colors = welshPowell(g);
        clock_t end = clock();
        double seconds = elapsed(start, end);
        fprintf(f, "%d,%.4f,%lld,%.9f,%d\n", n, p, edges, seconds, colors);
        printf("n=%d, arêtes=%lld, couleurs=%d, temps=%.6f s\n", n, edges, colors, seconds);
        freeGraph(g);
    }
    fclose(f);
    printf("Résultats enregistrés dans %s\n", out);
    return 0;
}
