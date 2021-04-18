/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 18/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef BITMAP_H
#define BITMAP_H

#include <stdlib.h>

/* --- CONSTANTS ------------------------------------------ */

#define WORD_SIZE 	(32)		/* int is 32 bits */
#define WORD_COUNT	(4)			/* 4*32 = 128 */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef unsigned int Word;

typedef struct {
	Word words[WORD_COUNT];
} Bitmap_128;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns the value of a single bit in the bitmap for a given index */
int getBit(void *bitmap, int index);
/* sets a single bit to 1 for a given index in the bitmap */
void setBit(void *bitmap, int index);
/* sets a single bit to 0 for a given index in the bitmap */
void clearBit(void *bitmap, int index);


#endif