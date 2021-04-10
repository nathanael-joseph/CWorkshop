/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 09/04/2021
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
Buffer *bufferInit() {
	Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
	if(buffer != NULL) {
		buffer->data = (char*)calloc(BUFFER_SIZE_INIT, sizeof(char));
		if(buffer->data == NULL) {
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
int bufferWriteChar(Buffer *buffer, char c) {

	if(buffer->currentSize == buffer->size) {
		buffer->size *= 2;
		buffer->data = realloc(buffer->data, buffer->size);
		if (buffer->data == NULL) {
			return -1;
		}
	}

	buffer->data[buffer->currentSize++] = c;

	return 0;
}

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char bufferReadChar(Buffer *buffer) {
	/* TODO */
	if(buffer->read < buffer->currentSize) {
		return buffer->data[buffer->read++];
	}
	return EOF;
}
