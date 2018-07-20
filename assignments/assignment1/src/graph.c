#include <stdlib.h>
#include "graph.h"
#include <stdio.h>

/*
  function that runs one time to create the vertices
  when we initialise them in the read_graph-function
*/
vertex *createVertices(size_t n){
    vertex *v = calloc(n, sizeof(*v));
    for(size_t i = 0; i < n; i++){
        v[i].id = i;
    }
		return v;
}

graph *read_graph(char *filename) {
	graph *init = malloc(sizeof(graph));

	// open file in read mode
	FILE *file = fopen(filename, "r");

	// create placeholder for data
	size_t atLine = 0;
	char *myString = NULL;

	// read first line in text-file
	getline(&myString, &atLine, file);

	// convert char to integer
  init->number_vertices = atoi(myString);
  init->vertices = createVertices(init->number_vertices);

  // With this loop we go through the rows of the matrix with getline,
	for(size_t i = 0; i < (init->number_vertices); i++){
		getline(&myString, &atLine, file);
    // here we loop coloumn wise through the matrix
		for(size_t j = 0; j < (init->number_vertices); j++){
      // if we find a '1'
			if('1'==myString[j]){
        /*
          first we check if list in initialised then,
          based on the coordinates(i,j) where the '1' is found 'i' will be
          having an outgoing nabour to j, and j will have an ingoing nabour to
          i (i->j)
        */
        if(init->vertices[i].out_neighbours){
          add_element(init->vertices[i].out_neighbours, init->vertices + j);
        } else {
          init->vertices[i].out_neighbours = init_linked_list(init->vertices + j);
        }

        if(init->vertices[j].in_neighbours){
          add_element(init->vertices[j].in_neighbours, init->vertices + i);
        } else {
          init->vertices[j].in_neighbours = init_linked_list(init->vertices + i);
        }
			}
		}
	}
	fclose(file);
	free(myString);
	return init;
}

void print_graph(graph *g) {

	printf("--I'm a graph!\n\n");

}
