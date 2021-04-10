/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef DYNAMIC_BUFFER_H
#define DYNAMIC_BUFFER_H

#include <stdlib.h>
#include "buffer.h"

/* --- CONSTANTS ------------------------------------------ */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef Buffer DynamicBuffer;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *dynamicBufferInit();

/* 
Adds the argument c to the dynamicBuffer. Returns -1 if the 
write failed, otherwise returns 0.
*/
int dynamicBufferWriteChar(void *buffer, char c);

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char dynamicBufferReadChar(void *buffer);

#endif