/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef SET_H
#define SET_H
 
#include "moretypes.h"
#include "bitmap_128.h"


/* --- CONSTANTS ------------------------------------------ */
/* --- TYPE DEFINITIONS ----------------------------------- */

typedef Bitmap_128 Set;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns a new set struct, an empty set */
Set *set_init();
/* adds argument x to the set */
void set_insert(void *set, int x);
/* returns true if the set contains x, false otherwise */
Boolean set_contains(const void *set, int x);
/* returns true if the set is empty, false otherwise */
Boolean set_isEmpty(const void *set);
/* returns a new set that is the union of set_a and set_b */
Set *set_union(const void *set_a, const void *set_b);
/* returns a new set that is the intersect of set_a and set_b */
Set *set_intersect(const void *set_a, const void *set_b);
/* returns a new set that is (set_a \ set_b) */
Set *set_subtract(const void *set_a, const void *set_b);
/* returns a new set that is the symetric differense of set_a and set_b */
Set *set_symetricDifference(const void *set_a, const void *set_b);
/* copies the contents of set_b into set_a */
void set_copy(void *set_a, const void *set_b);

#endif