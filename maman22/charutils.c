/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 03/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "charutils.h"

/* ---  LOCAL CONSTANTS ---------------------------------------- */

const char WHITESPACES_ARR[] = {' ', '\t', '\r', '\n', '\v'};


/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, 0 otherwise */
Boolean char_isWhitespace(char c) {
	int i;
	for( i = 0; i < WHITESPACES_ARR_LEN; i++) {
		if (c == WHITESPACES_ARR[i])
			return true;
	}
	return false;
}

/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
Boolean char_isLowerCase(char c) {
	if(c >= LOWERCASE_START && c <= LOWERCASE_END) 
		return true;
	return false;
}

/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
Boolean char_isUpperCase(char c) 
{
	if(c >= UPPERCASE_START && c <= UPPERCASE_END) 
		return true;
	return false;
}

/* returns 1 if c is in the range '0' -'9', 0 otherwise */
Boolean char_isNumber(char c) 
{
	if(c >= NUMBERS_START && c <= NUMBERS_END)
		return true;
	return false;
}
