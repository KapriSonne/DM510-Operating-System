#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef vertex* set;


// we create an array of pointers to vertices where a pointer is initialised to
// zero if the vertex has ingoing nabours, otherwise it will point the
// vertex it self.
set * no_edges(graph *g){
  set *S = calloc(g->number_vertices, sizeof(*S));
  for (size_t i = 0; i < g->number_vertices; i++) {
    if(!(g->vertices[i].in_neighbours)) S[i] = g->vertices+i;
  }
  return S;
}

// scans the array and returns the first pointer which isnt zero.
vertex * retrive(set *S, size_t n){
  for (size_t i = 0; i < n; i++) {
    if(S[i]){
      vertex * old = S[i];
      S[i] = NULL;
      return old;
    }
  }
  return NULL;
}

// follows the pseudocode on Kahns algorithm
void cycle_detection(graph *g) {
  linked_list *list = NULL;
  set *S = no_edges(g);
  vertex *n;
  while((n=retrive(S,g->number_vertices)) ){
    if(list){
      add_element(list, n);
    } else{
      list = init_linked_list(n);
    }
    for (linked_list * l = n->out_neighbours ; l ; l = l ->next) {
      vertex * m = (vertex *)l->data;
      remove_element(&m->in_neighbours,n);
      if(!m->in_neighbours) {
        S[m->id] = m;
      }
    }
  }
  free(S);
  for (size_t i = 0; i < g->number_vertices; i++) {
    if(g->vertices[i].in_neighbours) {
      printf("CYCLE DETECTED!\n");
      return;
    }
  }
  while(list) {
    vertex *m = list->data;
    printf("%d%s", m-> id, list->next ? ", " : "\n");
    remove_first(&list);
  }
}
