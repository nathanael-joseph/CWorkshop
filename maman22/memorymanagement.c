/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "memorymanagement.h"

#undef malloc
#undef calloc
#undef realloc 

/* --- PRIVATE FUNCTION DEFINITIONS --------------------------------- */

/* --- FUNCTION DEFINITIONS ----------------------------------------- */

void *mm_malloc(size_t size) {
	void *ptr;

	if((ptr = malloc(size)) == NULL) {
		em_throwMemoryAllocationErorr();	/* will call exit(-1) */
	} 

	return ptr;
}

void *mm_calloc(size_t nitems, size_t size) {
	void *ptr;
	if((ptr = calloc(nitems, size)) == NULL) {
		em_throwMemoryAllocationErorr();	/* will call exit(-1) */
	} 

	return ptr;
}

void *mm_realloc(void *ptr, size_t size) {

	if((ptr = realloc(ptr, size)) == NULL) {
		em_throwMemoryAllocationErorr();	/* will call exit(-1) */
	} 

	return ptr;
}
