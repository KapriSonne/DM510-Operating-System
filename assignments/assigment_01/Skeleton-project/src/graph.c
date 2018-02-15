#include <stdlib.h>
#include "graph.h"
#include <stdio.h>


graph *read_graph(char *filename) {
	FILE *file = fopen(filename, "r");
	if(file == 0){
		printf("file could not open\n\n");
	} else {
		int x;
		while  ( ( x = fgetc( file ) ) != EOF )
		{
				printf( "%c", x );
		}
		fclose(file);
	}
}

void print_graph(graph *g) {

}
