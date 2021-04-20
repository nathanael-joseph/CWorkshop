/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 20/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "set.h"

/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* returns a new set struct (an empty set) */
Set *setInit() {
	return bitmap_128_init();
}
/* adds argument x to the set */
void setInsert(void *set, int x) {
	setBit(set, x);
}
/* returns true if the set contains x, false otherwise */
Boolean setContains(void *set, int x) {
	return getBit(set, x);
}
/* returns a new set that is the union of set_a and set_b */
Set *setUnion(void *set_a, void *set_b) {
	Set *result, *A, *B;
	int i;

	A = set_a; 
	B = set_b; 
	result = setInit();

	for(i = 0; i < WORD_COUNT; i++) {
		result->words[i] = A->words[i] | B->words[i];
	}

	return result;

}
/* returns a new set that is the intersect of set_a and set_b */
Set *setIntersect(void *set_a, void *set_b) {
	Set *result, *A, *B;
	int i;

	A = set_a; 
	B = set_b; 
	result = setInit();

	for(i = 0; i < WORD_COUNT; i++) {
		result->words[i] = A->words[i] & B->words[i];
	}

	return result;
}
/* returns a new set that is (set_a \ set_b) */
Set *setSubtract(void *set_a, void *set_b) {
	Set *result, *A, *B;
	int i;

	A = set_a; 
	B = set_b; 
	result = setInit();

	for(i = 0; i < WORD_COUNT; i++) {
		result->words[i] = A->words[i] & (~B->words[i]); 
	}

	return result;
}
/* returns a new set that is the symetric differense of set_a and set_b */
Set *setSymetricDifference(void *set_a, void *set_b) {
	Set *result, *A, *B;
	int i;

	A = set_a; 
	B = set_b; 
	result = setInit();

	for(i = 0; i < WORD_COUNT; i++) {
		result->words[i] = 
			(A->words[i] & (~B->words[i])) | (B->words[i] & (~A->words[i])); 
			/* (A\B)U(B\A) */
	}

	return result;
}
