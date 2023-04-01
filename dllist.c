/**
 * CS 2110 - Spring 2017 - Homework #10
 *
 * @author Hardik Sangwan
 *
 * dllist.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

/* The node struct. Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO */
/* Design consideration: Only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES */
typedef struct dnode
{
    struct dnode* prev; /* Pointer to previous node */
    struct dnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;

/* Do not create any global variables here. Your dllist library should obviously
 * work for multiple concurrent dllists */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the dllist
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
    if (data == NULL) {
    	return NULL;
    }
    node *temp = malloc(sizeof(node));
    if (temp == NULL) {
    	return NULL;
    }
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = data;
    return temp;
}

/** create_dllist
  *
  * Creates a dllist by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty dllist
  */
dllist* create_dllist(void)
{
    /// @todo Implement changing the return value!
    dllist *temp = malloc(sizeof(dllist)); 
    if (temp == NULL) {
    	return NULL;
    }
    temp->head = NULL;
    temp->tail = NULL;
    temp->size = 0;
    return temp;
}

/** push_front
  *
  * Adds the data to the front of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_front(dllist *d, void *data)
{
    /// @todo Implement
	if (d == NULL || data == NULL) {
    	return;
    }
    node *temp = create_node(data);
    if (temp == NULL) {
    	return;
    }
    if (d->head == NULL) {
    	d->tail = temp;
    	d->head = temp;
    } else {
	    temp->next = d->head;
	    d->head->prev = temp;
	    d->head = temp;
	}
	d->size = d->size + 1;
}

/** push_back
  *
  * Adds the data to the back of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_back(dllist *d, void *data)
{
    /// @todo Implement
    if (d == NULL || data == NULL) {
    	return;
    }
    node *temp = create_node(data);
    if (temp == NULL) {
    	return;
    }
    if (d->tail == NULL) {
    	d->head = temp;
    	d->tail = temp;
    } else {
	    temp->prev = d->tail;
	    d->tail->next = temp;
	    d->tail = temp;
	}
    d->size = d->size + 1;
}

/** front
  *
  * Gets the data at the front of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist
  * @return The data at the first node in the dllist or NULL.
  */
void *front(dllist *d)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember, the
    /// user should never deal with the dllist nodes.
    if (d == NULL) {
    	return NULL;
    }
    if (d->head == NULL) {
    	return NULL;
    }
    return d->head->data;
}

/** back
  *
  * Gets the data at the "end" of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist structure
  * @return The data at the last node in the dllist or NULL.
  */
void *back(dllist *d)
{
    /// @todo Implement changing the return value!
    if (d == NULL) {
    	return NULL;
    }
    if (d->tail == NULL) {
    	return NULL;
    }
    return d->tail->data;
}

/** get
  *
  * Gets the data at the specified index in the dllist
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the dllist or NULL if index is
  *         out of range of the dllist.
  */
void *get(dllist *d, int index)
{
    /// @todo Implement changing the return value!
    if (index >= d->size || index < 0) {
    	return NULL;
    }
    node *current;
    if (index == 0) {
    	return d->head->data;
    } else if (index == (d->size - 1)) {
    	return d->tail->data;
    } else {
    	int counter = 0;
    	current = d->head;
    	while (counter < index) {
    		current = current->next;
    		counter++;
    	}
    }
    return current->data;
}
/** add
  *
  * Adds the data at the specified index in the dllist.
  * Adding at index size should have the same behavior as push_back
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head, to size.
  * @return true if insertion was successful or false if index is
  *         out of range of the dllist.
  */
bool add(dllist *d, void* data, int index)
{
    /// @todo Implement changing the return value!
   if (index > size(d) || index < 0) {
    	return false;
    }
   if (index == size(d)) {
	if (d == NULL || data == NULL) {
    	    return false;
    	}
    	node *temp = create_node(data);
    	if (temp == NULL) {
    	    return false;
    	}
    	if (d->tail == NULL) {
    	    d->head = temp;
    	    d->tail = temp;
    	} else {
	    temp->prev = d->tail;
	    d->tail->next = temp;
	    d->tail = temp;
	}
    	d->size = d->size + 1;
	return true;
    }
    if ((d == NULL) && (index != 1)) {
        return false;
    }
    if (index == 0) {
    	d->head->data = data;
	d->size = d->size + 1;
	return true;
    } else if (index == (size(d) - 1)) {
    	d->tail->data = data;
	d->size = d->size + 1;
	return true;
    } else {
    	int counter = 0;
	node *current = d->head;
    	while (counter < index) {
    		current = current->next;
    		counter++;
    	}
	node* temp = create_node(data);
	temp->prev = current;
	temp->next = current->next;
	current->next->prev = temp;
	current->next = temp;
	d->size = d->size + 1;
	return true;
    }
	
}

/** contains
  *
  * Traverses the dllist, trying to see if the dllist contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a dllist of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the dllist which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param d a pointer to the dllist structure
  * @param data The data, to see if it exists in the dllist
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the dllist, or NULL if it doesn't exist
  */
void *contains(dllist *d, void *data, dllist_eq eq_func) {
    /// @todo Implement
    if (d == NULL || data == NULL || eq_func == NULL) {
    	return NULL;
    }
	int counter = 0;
	node* current = d->head;
	while (counter < d->size) {
		if (eq_func(current->data, data) == 0) {
			return current->data;
		}
		counter++;
		current = current->next;
	}

    return NULL;
}

/** pop_front
  *
  * Removes the node at the front of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_front(dllist *d)
{
    /// @todo Implement
    if (d == NULL) {
    	return NULL;
    }
    if (d->size == 0) {
    	return NULL;
    }
    if (d->size == 1) {
    	node *temp = d->head;
    	d->head = NULL;
    	d->tail = NULL;
    	d->size--;
    	void *retval = temp->data;
    	free(temp);
    	return retval;
    }
    node *nodeToBeRemoved = d->head;
    void *retval = nodeToBeRemoved->data;
    d->head = nodeToBeRemoved->next;
    d->head->prev = NULL;
    d->size--;
    free(nodeToBeRemoved);
    return retval;
}

/** pop_back
  *
  * Removes the node at the end of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_back(dllist *d)
{
    /// @todo Implement
    if (d == NULL) {
    	return NULL;
    }
    if (d->size == 0) {
    	return NULL;
    }
    if (d->size == 1) {
    	node *temp = d->head;
    	d->head = NULL;
    	d->tail = NULL;
    	d->size--;
    	void *retval = temp->data;
    	free(temp);
    	return retval;
    }
    node *nodeToBeRemoved = d->tail;
    void *retval = nodeToBeRemoved->data;
    d->tail = nodeToBeRemoved->prev;
    d->tail->next = NULL;
    d->size--;
    free(nodeToBeRemoved);
    return retval;
}

/** copy_dllist
  *
  * Create a new dllist structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param d A pointer to the dllist structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this dllist, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the dllist for in your test
  * @return The dllist structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
dllist* copy_dllist(dllist *d, dllist_copy copy_func)
{
	if (d == NULL || copy_func == NULL) {
		return NULL;
	}
	int counter = 0;
	node *current = d->head;
	dllist *new_dllist = create_dllist();
	while (counter < d->size) {
		push_back(new_dllist, copy_func(current->data));
		counter++;
		current = current->next;
	}
	return new_dllist;
}

/** size
  *
  * Gets the size of the dllist
  *
  * @param d a pointer to the dllist structure
  * @return The size of the dllist
  */
int size(dllist *d)
{
    ///@note simply return the size of the dllist. It's that easy!
    if (d == NULL) {
    	return 0;
    }
    return d->size;
}

/** is_empty
  *
  * Checks to see if the dllist is empty.
  *
  * @param d a pointer to the dllist structure
  * @return true if the dllist is indeed empty, or false otherwise.
  */
bool is_empty(dllist *d)
{
    /// @note an empty dllist should have a size of zero and head points to NULL.
    if (d == NULL) {
    	return 0;
    }
    return d->size == 0 ? 1 : 0;
}

/** empty_dllist
  *
  * Empties the dllist. After this is called, the dllist should be empty.
  * This does not free the dllist struct itself, just all nodes and data within.
  *
  * @param d a pointer to the dllist structure
  * @param free_func function used to free the nodes' data.
  */
void empty_dllist(dllist *d, dllist_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes, not the dllist structure itself.
    /// @note do not free the dllist structure itself.
    if (d == NULL || free_func == NULL) {
    	return;
    }
    node *temp = d->head;
    node *temp2;
    while (temp != NULL) {
    	free_func(temp->data);
    	temp2 = temp->next;
    	free(temp);
    	temp = temp2;
    	d->size--;
    }
    d->head = NULL;
    d->tail = NULL;
}

/** traverse
  *
  * Traverses the dllist, calling a function on each node's data.
  *
  * @param d a pointer to the dllist structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(dllist *d, dllist_op do_func)
{
    /// @todo Implement
    int counter = 0;
    node *current = d->head;
    while (counter < d->size) {
    	do_func(current->data);
    	current = current->next;
    	counter++;
    }
}

/** reverse
  * Reverses the dllist
  * Should do nothing if d is NULL
  * @param d a pointer to the dllist structure
  */
void reverse(dllist *d) {
    /// @todo Implement
    node *temp = NULL;
    node *current = d->head;
    while (current != NULL) {
    	temp = current->prev;
	current->prev = current->next;
	current->next = temp;
	current = current->prev;
    }
    if (temp != NULL) {
	d->head = temp->prev;
    }
}
