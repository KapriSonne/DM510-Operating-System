/*
 * linked_list.c
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/*

typedef struct  linked_list{
	void *data;
	struct linked_list *next;
	struct linked_list *previous;
} linked_list;

*/
linked_list *init_linked_list() {
	// we initialize a root on the stack that points to the first
	// element in our linked list on the heap
	linked_list *root;
	root = malloc(sizeof(struct linked_list));
	// set everything to NULL
	root -> data = NULL;
	root -> previous = NULL;
	root -> next = NULL;
	return root;
}

void add_element( linked_list *list, void *element) {
	
	root->next = malloc(sizeof(struct linked_list));
}

int linked_list_size(linked_list *list) {
	return 0;
}

void *remove_first(linked_list *list) {
	return NULL;
}

int remove_element(linked_list *list, void *element) {
	return -1;
}
