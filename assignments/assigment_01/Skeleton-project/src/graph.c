#include <stdlib.h>
#include "graph.h"
#include <stdio.h>

/*

typedef struct graph {
	int number_vertices;
	vertex *vertices;
} graph;

typedef struct vertex {
	int id;
	linked_list *out_neighbours;
	linked_list *in_neighbours;
} vertex;

*/


graph *read_graph(char *filename) {
	FILE *file = fopen(filename, "r");
	char *myString = NULL;
	size_t where_am_I = 0;

	getline(&myString, &where_am_I, file);
	long int sizeOfVertices = strtol(myString, NULL, 10);

	// for debugging purposes.
	printf("\nNo. of vertices: %li\n-------------------\n",sizeOfVertices);

	for(int i = 0; i < sizeOfVertices; i++){
		where_am_I++;
		getline(&myString, &where_am_I, file);
		long int getVertices = strtol(myString, NULL, 10);
		printf("%li\n",getVertices);
	}
	printf("\n");
}



void print_graph(graph *g) {

}
