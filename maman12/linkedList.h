/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 09/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H	

/* --- CONSTANTS ------------------------------------------ */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef node Node;

struct node {
	char data;
	Node *next;
}

typedef struct {
	Node *head; /* head node will be empty node, do not read */
	Node *tail;
	Node *read;
} LinkedList;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation.
*/
LinkedList *linkedListInit();

/* 
Adds the argument c to the linkedList. Returns -1 if the 
write failed, otherwise returns 0.
*/
int linkedListWriteChar(LinkedList *list, char c);

/* 
Returns the next char from the linkedList or EOF if the 
linkedList has been read to the end.
*/
char linkedListReadChar(LinkedList *list);


#endif