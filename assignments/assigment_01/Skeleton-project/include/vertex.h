#ifndef VERTEX_H_
#define VERTEX_H_

#include "linked_list.h"

// Datastructure for a vertex in a graph
typedef struct vertex {
	int id;
	linked_list *out_neighbours;
	linked_list *in_neighbours;
} vertex;

#endif /* VERTEX_H_ */
