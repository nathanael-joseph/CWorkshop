/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 19/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef BITMAP_H
#define BITMAP_H

#include <stdlib.h>

/* --- CONSTANTS/MACROS ----------------------------------- */

#define WORD_SIZE 	(32)		/* int is 32 bits */
#define WORD_COUNT	(4)			/* 4*32 = 128 */
#define WORD_OFFSET(x) (x / WORD_SIZE)
#define BIT_OFFSET(x) (x % WORD_SIZE) 

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef unsigned int Word;

typedef struct {
	Word words[WORD_COUNT]; 
	/* Word *words; */
} Bitmap_128;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/*
TODO: modify bitmap init function to trhow an error, instead of returning NULL
*/

/* returns a pointer to a new insatnce of a bitmap, or null if malloc fails */
Bitmap_128 *bitmap_128_init();
/* returns the value of a single bit in the bitmap for a given index */
int bitmap_128_getBit(void *bitmap, int index);
/* sets a single bit to 1 for a given index in the bitmap */
void bitmap_128_setBit(void *bitmap, int index);
/* sets a single bit to 0 for a given index in the bitmap */
void bitmap_128_clearBit(void *bitmap, int index);


#endif