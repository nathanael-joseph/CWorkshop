/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef BUFFER_H
#define BUFFER_H	

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

/* --- CONSTANTS ------------------------------------------ */
#define BUFFER_SIZE_INIT (256)

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef struct {
	long unsigned int size; /* the physical size of data array */
	long unsigned int currentSize; /* size of data in use */
	long unsigned int read; /* index of last read element in data array */
	char *data;
} Buffer;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* Returns true if the buffer's data array is full, false otherwise */
boolean isFullBuffer(void *buffer);

/* Returns true if buffer's data array has been completely read, false otherwise */
boolean hasBeenReadBuffer(void *buffer);

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *bufferInit();

/* 
Adds the argument c to the buffer. Returns -1 if the 
write failed, otherwise returns 0.
*/
int bufferWriteChar(void *buffer, char c);

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char bufferReadChar(void *buffer);


#endif	