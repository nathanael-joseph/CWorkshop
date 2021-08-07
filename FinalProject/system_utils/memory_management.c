/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "memory_management.h"

#undef malloc
#undef calloc
#undef realloc 

/* --- PRIVATE FUNCTION DEFINITIONS --------------------------------- */
static void mm_throwMemoryAllocationErorr() {
	fputs("A memory allocation Error occured... \nExiting... \n", stderr);
	exit(MEM_ALLOC_ERR);
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

void *mm_malloc(size_t size) {
	void *ptr;

	if((ptr = malloc(size)) == NULL) {
		mm_throwMemoryAllocationErorr();	/* will call exit(-5) */
	} 

	return ptr;
}

void *mm_calloc(size_t nitems, size_t size) {
	void *ptr;
	if((ptr = calloc(nitems, size)) == NULL) {
		mm_throwMemoryAllocationErorr();	/* will call exit(-5) */
	} 
	return ptr;
}

void *mm_realloc(void *ptr, size_t size) {

	if((ptr = realloc(ptr, size)) == NULL) {
		mm_throwMemoryAllocationErorr();	/* will call exit(-5) */
	} 

	return ptr;
}
