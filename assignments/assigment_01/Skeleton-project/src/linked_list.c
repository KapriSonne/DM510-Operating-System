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

int main() {
  linked_list * mystacklist = init_linked_list();
  int a = 5;
  add_element(mystacklist,&a);
  add_element(mystacklist,&a);
  add_element(mystacklist,&a);
  return 0;
}

*/

/*

typedef struct  linked_list{
	void *data;
	struct linked_list *next;
	struct linked_list *previous;
} linked_list;

*/
linked_list *init_linked_list() {
	// create list root on stack
	linked_list *root;
	// allocate root on heap on point to it
	root = malloc(sizeof(linked_list));
	// assign NULL to all
	root -> data = NULL;
	root -> previous = NULL;
	root -> next = NULL;
	return root;
}

void add_element(linked_list *list, void *element) {
	// allocate newNode on heap
	linked_list *newNode = malloc(sizeof(linked_list));
	// assign the value from element to data
	newNode->data = element;

	// if (list->previous) then *old = list->previous
	// else *old = list
	linked_list *old = list->previous ? list->previous : list;

	list->previous = newNode;
	// make old node's 'next' point to the new node in the list
	old->next = newNode;
	// make new node's 'prevous' point to the old node in the list
	newNode->previous = old;
	// make last node's 'next' point to first node in the list
	newNode->next = list;
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
