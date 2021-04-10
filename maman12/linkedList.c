/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "linkedList.h"


/* --- FUNCTION DEFINITIONS -------------------------------- */


/* 
Returns a pointer to a new instance of a Node struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *nodeInit(){
	
	Node *node = malloc(sizeof(*node));
	
	if (node != NULL) {

		node->next = NULL;

		node->buffer = bufferInit();
		if(node->buffer == NULL) {
			return NULL; /* node's buffer could not be created */
		}
	} 

	return node;
}

/* 
Returns a pointer to a new instance of a LinkedList struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *linkedListInit() {

	LinkedList *list = malloc(sizeof(*list));

	if (list != NULL) {	

		list->head = nodeInit();
		if (list->head == NULL) {
			return NULL; /* head node could not be created */
		}
		
		list->tail = list->head;
		list->read = list->head;
	} 

	return list;
}

/* 
Adds the argument c to the linkedList. Returns -1 if the 
write failed, otherwise returns 0.
*/
int linkedListWriteChar(void *linkedList, char c) {

	LinkedList *list = (LinkedList *)linkedList;
	
	Buffer *currentBuffer = list->tail->buffer;
	
	if (isFullBuffer(currentBuffer)) {
		
		list->tail->next = nodeInit();
		if (list->tail->next == NULL) {
			return -1;  /* next node could not be created*/
		}

		list->tail = list->tail->next;
		currentBuffer = list->tail->buffer;
		
	}
	
	bufferWriteChar(currentBuffer, c);
	
	return 0;
}

/* 
Returns the next char from the linkedList or EOF if the 
linkedList has been read to the end.
*/
char linkedListReadChar(void *linkedList) {

	LinkedList *list = (LinkedList *)linkedList;
	Buffer *currentBuffer = list->read->buffer;

	if(hasBeenReadBuffer(currentBuffer)) {
		
		list->read = list->read->next;
		if(list->read  == NULL) {
			return EOF;
		}

		currentBuffer = list->read->buffer;
	}

	return bufferReadChar(currentBuffer);
}

