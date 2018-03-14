README:
------
I've made some few changes to some of the functions arguments and the
linked_list struct which I will elaborate in greater details below.
(You'll find much of the same commented in the sourcecode.)

My program should handle all cornercases, every task i completed and
it passes all test.

	#################################
	#				#
	#	  linked_list.c		#
	#				#
	#################################

linked_list struct:
---------------------------------------------
To keep track of the number of nodes in the list (list size), I've added a 'int size'
to the struct. This size will be initialized with the first node created in the list,
and then act as a counter. Meaning, everytime we call add_element-function, we will
recursively update and increment size by one on each node in the list.
e.g: if we have three nodes in list:

	- node 1 has size = 3
	- node 2 has size = 2
	- node 3 has size = 1

That way, if we want to know the total size of the list, we just look at the first node's
size.



init_linked_list:
---------------------------------------------
I've added a void pointer to element as parameter because i want to initialize
the first node with an element, otherwise - because of the way 'add_element'-function
is implemented - we would have an empty node (no data) that points to the first real node.



add_element:
---------------------------------------------
if list hast no next-pointer we are at the end of our list, so we initialize a
new node and update its pointers and finally increment the list size by one.

if it does have a next pointer it means we are not at the end of the list, so
we recursivly traverse to the end before adding a new node, then we update
pointers etc.



linked_list_size
---------------------------------------------
Simply returns the list-size by looking at the first node in list's size.



remove_first
---------------------------------------------
I've changed the argument to take a double pointer instead of a single pointer
because we are removing the first element such that the input variable
will point to the next node in list.



remove_element
---------------------------------------------
I've changed the argument to take a double pointer instead of a single pointer
because if we delete a node, that pointer would be invalid, with a double
pointer we obtain the abilty to change the pointer pointing to the element.


	#################################
	#				#
	#	     graph.c		#
	#				#
	#################################



createVertices
---------------------------------------------
Created this function which runs one time to create the vertices
when we initialise them in the read_graph-function



read_graph
---------------------------------------------
We read the first line of the text file with getline to retrieve the number of vertices.
Then we look through the rest of the lines in file, also with getline, rows and coloumn-wise
until we discover a '1'. Based on the coordinates(i,j) where the '1' is found, 'i' will
be having an outgoing neighbour to j, and j will have an ingoing neighbour to i (i->j)


	#################################
	#				#
	#       cycledetection.c	#
	#				#
	#################################



noEdges
---------------------------------------------
We create an array of pointers to vertices where a pointer is initialised to
zero if the vertex has ingoing nabours, otherwise it will point the
vertex it self.



get
---------------------------------------------
This function scans the array (or set) and returns the first pointer which isnt zero.



cycle_detection
---------------------------------------------
Based on the pseudo code for Kahns algorithm
