/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef MEMORYMANAGEMENT_H
#define MEMORYMANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include "errormanagement.h"

/* 
This header file overrides the malloc, realloc, and calloc functions.
If a memory allocation error occurs, an error message will be printed
to stderr, and the program will exit, returning -1.
*/

/* --- MACRO OVERRIDES ------------------------------------ */

#define malloc(size) mm_malloc(size)
#define calloc(nitems, size) mm_calloc(nitems, size)
#define realloc(ptr, size) mm_realloc(ptr, size)

/* --- TYPE DEFINITIONS ----------------------------------- */

/* --- FUNCTION DECLARATIONS ------------------------------ */

void *mm_malloc(size_t size);

void *mm_calloc(size_t nitems, size_t size);

void *mm_realloc(void *ptr, size_t size);

#endif