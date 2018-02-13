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
	linked_list *root;
	root = malloc(sizeof(linked_list));
	root -> data = NULL;
	root -> previous = NULL;
	root -> next = NULL;
	return root;
}

void add_element(linked_list *list, void *element) {

	linked_list *newNode = malloc(sizeof(linked_list));
	newNode->data = element;

	// '?' inline if-statement
	linked_list *old = list->previous ? list->previous : list;
	list->previous = newNode;

	old->next = newNode;
	newNode->previous = old;
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
