/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H	


#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

/* --- CONSTANTS ------------------------------------------ */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef struct node Node;

struct node {
	Buffer *buffer;
	Node *next;
};

typedef struct {
	Node *head; /* head node will be garbage node, do not read */
	Node *tail;
	Node *read;
} LinkedList;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* 
Returns a pointer to a new instance of a Node struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *nodeInit();

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *linkedListInit();

/* 
Adds the argument c to the linkedList. Returns -1 if the 
write failed, otherwise returns 0.
*/
int linkedListWriteChar(void *linkedList, char c);

/* 
Returns the next char from the linkedList or EOF if the 
linkedList has been read to the end.
*/
char linkedListReadChar(void *linkedList);


#endif