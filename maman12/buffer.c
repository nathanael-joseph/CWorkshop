/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "buffer.h"


/* --- FUNCTION DEFINITIONS -------------------------------- */

/* returns true if the buffer's data array is full, false otherwise */
boolean isFullBuffer(void *buffer) {
	Buffer *bfr = (Buffer*)buffer;	
	return bfr->currentSize == bfr->size;
}

/* Returns true if buffer's data array has been completely read, false otherwise */
boolean hasBeenReadBuffer(void *buffer) {
	Buffer *bfr = (Buffer*)buffer;
	return bfr->read == bfr->currentSize;
}

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
void *bufferInit() {

	Buffer *buffer = malloc(sizeof(*buffer));

	if (buffer != NULL) {
		buffer->data = calloc(BUFFER_SIZE_INIT, sizeof(*buffer->data));

		if (buffer->data == NULL) {
			return NULL; /* could not create data array */
		}

		buffer->size = BUFFER_SIZE_INIT;
		buffer->currentSize = 0;
		buffer->read = 0;
	}

	return buffer;
}

/* 
Adds the argument c to the buffer. Returns EOF if the 
insert failed, otherwise returns argument c.
*/
int bufferWriteChar(void *buffer, char c) {
	Buffer *bfr = (Buffer*)buffer;

	if (isFullBuffer(bfr)) {
		return -1;
	}

	bfr->data[bfr->currentSize++] = c;
	return 0;
}

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char bufferReadChar(void *buffer) {

	Buffer *bfr = (Buffer*)buffer;

	if (bfr->read < bfr->currentSize) {
		return bfr->data[bfr->read++];
	}

	return EOF;
}
