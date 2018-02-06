#ifndef GRAPH_H_
#define GRAPH_H_

#include "vertex.h"

// Graph data structure
typedef struct graph {
	int number_vertices;
	vertex *vertices;
} graph;

/*
 * Reads in the file from the given filename
 * and build a graph from the input.
 */
graph *read_graph(char *filename);

/*
 * Debug method, that can print information on a supplied graph.
 */
void print_graph(graph *g);


#endif
