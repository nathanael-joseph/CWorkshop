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
 
#include "bitmap_128.h"
#include "boolean.h"

/* --- CONSTANTS ------------------------------------------ */
/* --- TYPE DEFINITIONS ----------------------------------- */

typedef Bitmap_128 Set;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns a new set struct, an empty set */
Set *setInit();
/* adds argument x to the set */
void setInsert(void *set, int x);
/* returns true if the set contains x, false otherwise */
Boolean setContains(void *set, int x);
/* returns a new set that is the union of set_a and set_b */
Set *setUnion(void *set_a, void *set_b);
/* returns a new set that is the intersect of set_a and set_b */
Set *setIntersect(void *set_a, void *set_b);
/* returns a new set that is (set_a \ set_b) */
Set *setSubtract(void *set_a, void *set_b);
/* returns a new set that is the symetric differense of set_a and set_b */
Set *setSymetricDifference(void *set_a, void *set_b);


/* functions to implement for code parser
read_set A , 1,2,3, ..., -1
print_set A
union_set A, B, C
intersect_set A, B, C
sub_set A, B, C
symdiff_set A, B, C
*/


#endif