
/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 23/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14 Question 1
-------------------------------------------------------------------------------
*/

#ifndef LINKEDLIST_BUFFER_H
#define LINKEDLIST_BUFFER_H	

#include <stdlib.h>
#include "more_types.h"
#include "system_utils/memory_management.h"
#include "datastructures/singlelinkedlist.h"

/* --- CONSTANTS ------------------------------------------ */

#define BUFFER_INIT_SIZE (256)


/* --- TYPE DEFINITIONS ----------------------------------- */

typedef struct linkedListBuffer LinkedListBuffer; 


/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns a pointer to a new linked list buffer */
void *LinkedListBuffer_init();

/* frees the linked list buffer  */
void LinkedListBuffer_free(void *linkedlistBuffer);

/* Writes a byte to the linked list buffer */
void LinkedListBuffer_writeByte(void *linkedlistBuffer, Byte byte);

/* Writes a string to the linked list buffer (not including the '\0' string ending) */
void LinkedListBuffer_writeString(void *linkedlistBuffer, String const str);

/* 
	Returns the next byte from the linked list buffer as an integer or EOF if the 
	buffer has been read to the end.
*/
int LinkedListBuffer_readByte(void *linkedlistBuffer);

/* returns true if no bytes have been written to buffer, else returns false */
Boolean LinkedListBuffer_isEmpty(void *linkedlistBuffer);

#endif	