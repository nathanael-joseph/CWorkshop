/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 09/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "linkedList.h"


/* --- FUNCTION DEFINITIONS -------------------------------- */

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation.
*/
LinkedList *linkedListInit() {
	LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
	if (list != NULL) {		
		list->head = (Node *)malloc(sizeof(Node));
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
int linkedListWriteChar(LinkedList *list, char c) {
	list->tail.next = (Node *)malloc(sizeof(Node));
	if (list->tail.next == NULL) {
		return -1;
	}

	list->tail = list->tail.next;
	list->tail.data = c;

	return 0;
}

/* 
Returns the next char from the linkedList or EOF if the 
linkedList has been read to the end.
*/
char linkedListReadChar(LinkedList *list) {
	if((list->read = list->read.next) != NULL) {
		return list->read.data;
	}

	return EOF;
}

