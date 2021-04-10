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

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation.
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

	if (bfr->currentSize == bfr->size) {

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
char bufferReadChar(void *buffer) {

	Buffer *bfr = (Buffer*)buffer;

	if (bfr->read < bfr->currentSize) {
		return bfr->data[bfr->read++];
	}

	return EOF;
}
