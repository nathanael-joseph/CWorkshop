/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 08/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef BUFFER_H
#define BUFFER_H	

#include <stdio.h>
#include <stdlib.h>

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

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation.
*/
Buffer *BufferInit();

/* 
Adds the argument c to the buffer. Returns EOF if the 
insert failed, otherwise returns argument c.
*/
char BufferWrite(Buffer *buffer, char c);

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char BufferRead(Buffer *buffer);


#endif	