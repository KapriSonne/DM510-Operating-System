#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "cycledetection.h"

/*
 * Prints the usage to the console.
 */
void show_usage() {
	printf("===================================\n");
	printf("=======     Usage      ============\n");
	printf("===================================\n");
	printf(" ./program graph-file \n");
	printf("===================================\n");
}

// help function to free the list from memory recursively.
void free_list(linked_list * list){
	if(list){
		free_list(list->next);
		free(list);
	}
}

// First command line parameter - input file
int main(int argc, char *argv[]) {

	// Error checking
	if( argc != 2) {
		show_usage();
		return 0;
	}

	// Build a graph from the input
	graph *g = read_graph(argv[1]);

	// Run cycle detection algorithm and output result
	cycle_detection(g);

	// For every vertex, free them, then free our graph.
	for (size_t i = 0; i < g->number_vertices; i++) {
		g->vertices[i];
		free_list(g->vertices[i].out_neighbours);
		free_list(g->vertices[i].in_neighbours);
	}
	free(g->vertices);
	free(g);

}
