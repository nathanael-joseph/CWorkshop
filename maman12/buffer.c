/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 08/04/2021
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
Buffer *BufferInit() {
	Buffer *bfr = (Buffer*)malloc(sizeof(Buffer));
	if(bfr != NULL) {
		bfr->data = (char*)calloc(BUFFER_SIZE_INIT, sizeof(char));
		if(bfr->data == NULL) {
			return NULL;
		}
		bfr->size = BUFFER_SIZE_INIT;
		bfr->currentSize = 0;
		bfr->read = 0;
	}
	return bfr;
}

/* 
Adds the argument c to the buffer. Returns EOF if the 
insert failed, otherwise returns argument c.
*/
char BufferWrite(Buffer *buffer, char c) {
	/* TODO */
	return EOF;
}

/* 
Returns the next char from the buffer or EOF if the 
buffer has been read to the end.
*/
char BufferRead(Buffer *buffer) {
	/* TODO */
	return EOF;
}
