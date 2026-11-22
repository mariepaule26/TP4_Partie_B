#include "graph0.h"
#include <string.h>

Graph *createGraph(int n) {
    if (n <= 0) return NULL;
    Graph *g = malloc(sizeof *g);
    if (!g) return NULL;
    g->n = n;
    g->A = calloc((size_t)n * (size_t)n, sizeof *g->A);
    g->colors = malloc((size_t)n * sizeof *g->colors);
    g->degrees = malloc((size_t)n * sizeof *g->degrees);
    if (!g->A || !g->colors || !g->degrees) {
        free(g->A); free(g->colors); free(g->degrees); free(g); return NULL;
    }
    for (int i = 0; i < n; ++i) { g->colors[i] = -1; g->degrees[i] = 0; }
    return g;
}

void addEdge(Graph *g, int u, int v) {
    if (!g || u < 0 || v < 0 || u >= g->n || v >= g->n || u == v) return;
    g->A[(size_t)u * g->n + v] = 1;
    g->A[(size_t)v * g->n + u] = 1;
}

int neighborUsingColor(const Graph *g, int vertex, int color) {
    if (!g || vertex < 0 || vertex >= g->n) return 0;
    for (int v = 0; v < g->n; ++v)
        if (g->A[(size_t)vertex * g->n + v] && g->colors[v] == color) return 1;
    return 0;
}

static void calculateDegrees(Graph *g) {
    for (int u = 0; u < g->n; ++u) {
        int d = 0;
        for (int v = 0; v < g->n; ++v) d += g->A[(size_t)u * g->n + v] != 0;
        g->degrees[u] = d;
    }
}

int welshPowell(Graph *g) {
    if (!g) return -1;
    int n = g->n;
    int *order = malloc((size_t)n * sizeof *order);
    if (!order) return -1;
    calculateDegrees(g);
    for (int i = 0; i < n; ++i) { order[i] = i; g->colors[i] = -1; }

    /* Tri décroissant des degrés. En cas d'égalité, l'indice croissant est conservé. */
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            int a = order[j], b = order[j + 1];
            if (g->degrees[a] < g->degrees[b]) {
                order[j] = b; order[j + 1] = a;
            }
        }
    }

    int color = 0;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (g->colors[u] != -1) continue;
        g->colors[u] = color;
        for (int j = i + 1; j < n; ++j) {
            int v = order[j];
            if (g->colors[v] == -1 && !neighborUsingColor(g, v, color))
                g->colors[v] = color;
        }
        ++color;
    }
    free(order);
    return color;
}

void displayAdjacency(const Graph *g) {
    if (!g) return;
    puts("Matrice d'adjacence :");
    for (int i = 0; i < g->n; ++i) {
        for (int j = 0; j < g->n; ++j) printf("%d ", g->A[(size_t)i * g->n + j]);
        putchar('\n');
    }
}
void displayDegres(const Graph *g) {
    if (!g) return;
    puts("Degrés :");
    for (int i = 0; i < g->n; ++i) printf("Sommet %d : %d\n", i, g->degrees[i]);
}
void displayColoring(const Graph *g) {
    if (!g) return;
    int count = 0;
    for (int i = 0; i < g->n; ++i) if (g->colors[i] + 1 > count) count = g->colors[i] + 1;
    printf("Nombre de couleurs : %d\n", count);
    for (int c = 0; c < count; ++c) {
        printf("Couleur %d : ", c);
        for (int v = 0; v < g->n; ++v) if (g->colors[v] == c) printf("%d ", v);
        putchar('\n');
    }
}
int dotExport(const Graph *g, const char *fileName) {
    if (!g || !fileName) return 0;
    FILE *f = fopen(fileName, "w");
    if (!f) return 0;
    static const char *palette[] = {"lightblue", "lightcoral", "lightgreen", "khaki", "plum", "orange", "turquoise", "wheat"};
    fprintf(f, "graph G {\n  node [style=filled];\n");
    for (int i = 0; i < g->n; ++i)
        fprintf(f, "  %d [fillcolor=\"%s\", label=\"%d (c%d)\"];\n", i, palette[g->colors[i] % 8], i, g->colors[i]);
    for (int i = 0; i < g->n; ++i)
        for (int j = i + 1; j < g->n; ++j)
            if (g->A[(size_t)i * g->n + j]) fprintf(f, "  %d -- %d;\n", i, j);
    fputs("}\n", f);
    return fclose(f) == 0;
}
void freeGraph(Graph *g) {
    if (!g) return;
    free(g->A); free(g->colors); free(g->degrees); free(g);
}
