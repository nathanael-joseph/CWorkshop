/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 23/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14 Question 1
-------------------------------------------------------------------------------
*/

#include "linkedlist_buffer.h"

static String _emptyString = "";	/* will be used as key for linked list nodes. */

/* --- PRIVATE STRUCT/TYPE DEFINITIONS --------------------- */

struct linkedListBuffer {
	SingleLinkedList *list;
	SingleLinkedListNode *currentReadNode;
	SingleLinkedListNode *currentWriteNode;	
	uint32_t count; /* the total number of bytes written */
};

typedef struct {
	uint32_t size; /* the physical size of bytes array */
	uint32_t read; /* index of the next array byte to read */
	uint32_t write; /* index of the next array byte to write to */
	Byte *bytes; /* the bytes array */
} Buffer;


/* --- STATIC FUNCTION DEFINITIONS -------------------------------- */

/* Returns true if the buffer's data array is full, false otherwise */
static Boolean Buffer_isFull(void *buffer) {
	Buffer *bfr = buffer;	
	return bfr->write == bfr->size;
}

/* Returns true if buffer's data array has been completely read, false otherwise */
static Boolean Buffer_hasBeenRead(void *buffer) {
	Buffer *bfr = buffer;
	return bfr->read == bfr->write;
}

/* 
Returns a pointer to a new instance of a Buffer struct, 
the caller is responsible for deallocation. Returns NULL
if memory allocation failed.
*/
static void *Buffer_init() {

	Buffer *buffer = malloc(sizeof(*buffer));
	buffer->bytes = calloc(BUFFER_INIT_SIZE, sizeof(*buffer->bytes));

	buffer->size = BUFFER_INIT_SIZE;
	buffer->write = 0;
	buffer->read = 0;

	return buffer;
}

/* frees the buffer */
static void Buffer_free(void *buffer) {
	Buffer *bfr = buffer;

	free(bfr->bytes);
	free(bfr);
}

/* 
	Writes a byte to the buffer. Returns false if the insert failed, 
	otherwise returns true.
*/
static Boolean Buffer_tryWriteByte(void *buffer, Byte byte) {
	Buffer *bfr = buffer;

	if (Buffer_isFull(bfr)) {
		return false;
	}

	bfr->bytes[bfr->write++] = byte;
	return true;
}

/* 
	Returns the next byte from the buffer as an integer or EOF if the 
	buffer has been read to the end.
*/
static int Buffer_readByte(void *buffer) {

	Buffer *bfr = buffer;

	if (bfr->read < bfr->write) {
		return bfr->bytes[bfr->read++];
	}

	return EOF;
}

/* --- FUNCTION DEFINITIONS -------------------------------- */

/* returns a pointer to a new linked list buffer */
void *LinkedListBuffer_init() {
	LinkedListBuffer *llb = malloc(sizeof(*llb));
	Buffer *headBuffer = Buffer_init();

	llb->list = SingleLinkedList_init();	
	SingleLinkedList_append(llb->list, _emptyString, headBuffer);

	llb->currentReadNode = llb->list->head;
	llb->currentWriteNode = llb->list->head;
	llb->count = 0;

	return llb;
}

/* frees the linked list buffer  */
void LinkedListBuffer_free(void *linkedlistBuffer) {
	LinkedListBuffer *llb = linkedlistBuffer;
	SingleLinkedList_freeWithCallback(llb->list, Buffer_free);
	free(llb);
}

/* Writes a byte to the linked list buffer */
void LinkedListBuffer_writeByte(void *linkedlistBuffer, Byte byte) {
	LinkedListBuffer *llb = linkedlistBuffer;
	
	if(Buffer_isFull(llb->currentWriteNode->data)) {
		Buffer *nextBuffer = Buffer_init();
		SingleLinkedList_append(llb->list, _emptyString, nextBuffer);
		llb->currentWriteNode = llb->currentWriteNode->next;
	}

	Buffer_tryWriteByte(llb->currentWriteNode->data, byte);

	llb->count++;
}

/* Writes a string to the linked list buffer (not including the '\0' string ending) */
void LinkedListBuffer_writeString(void *linkedlistBuffer, String const str) {
	int i; 
	for(i = 0; i < strlen(str); i++) {
		LinkedListBuffer_writeByte(linkedlistBuffer, str[i]);
	}
}

/* 
	Returns the next byte from the linked list buffer as an integer or EOF if the 
	buffer has been read to the end.
*/
int LinkedListBuffer_readByte(void *linkedlistBuffer) {
	LinkedListBuffer *llb = linkedlistBuffer;

	if(Buffer_hasBeenRead(llb->currentReadNode->data)) {
		llb->currentReadNode = llb->currentReadNode->next; 	
	}

	if(llb->currentReadNode != NULL) {
		return Buffer_readByte(llb->currentReadNode->data);
	} 

	return EOF;
}

/* returns true if no bytes have been written to buffer, else returns false */
Boolean LinkedListBuffer_isEmpty(void *linkedlistBuffer) {
	LinkedListBuffer *llb = linkedlistBuffer;
	
	if(llb->count == 0) {
		return true;
	}

	return false;
}
