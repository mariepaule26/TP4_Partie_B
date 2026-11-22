#ifndef GRAPH0_H
#define GRAPH0_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Graph {
    int n;
    unsigned char *A; /* matrice contigue : A[u*n + v] */
    int *colors;
    int *degrees;
} Graph;

Graph *createGraph(int n);
void addEdge(Graph *g, int u, int v);
int neighborUsingColor(const Graph *g, int vertex, int color);
int welshPowell(Graph *g); /* renvoie le nombre de couleurs */
void displayAdjacency(const Graph *g);
void displayDegres(const Graph *g);
void displayColoring(const Graph *g);
int dotExport(const Graph *g, const char *fileName);
void freeGraph(Graph *g);
#endif
