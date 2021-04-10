/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "dynamicBuffer.h"


/* --- FUNCTION DEFINITIONS -------------------------------- */

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *dynamicBufferInit() {
	return bufferInit();
}

/* 
Adds the argument c to the dynamicBuffer. Returns -1 if the 
write failed, otherwise returns 0.
*/
int dynamicBufferWriteChar(void *buffer, char c) {
	DynamicBuffer *bfr = (DynamicBuffer*)buffer;

	if (isFullBuffer(bfr)) {

		bfr->size *= 2;
		bfr->data = realloc(bfr->data, bfr->size);

		if (bfr->data == NULL) {
			return -1;
		}
	}

	bfr->data[bfr->currentSize++] = c;

	return 0;
}

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char dynamicBufferReadChar(void *buffer) {
	return bufferReadChar(buffer);
}


