/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 22/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "char_utils.h"

/* ---  LOCAL CONSTANTS ---------------------------------------- */

const char WHITESPACES_ARR[] = {' ', '\t', '\r', '\n', '\v'};


/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* returns true if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, false otherwise */
Boolean char_isWhitespace(char c) {
	int i;
	for( i = 0; i < WHITESPACES_ARR_LEN; i++) {
		if (c == WHITESPACES_ARR[i])
			return true;
	}
	return false;
}

/* returns true if c is in the range 'a' -'z', false otherwise */
Boolean char_isLowerCase(char c) {
	if(c >= LOWERCASE_START && c <= LOWERCASE_END) 
		return true;
	return false;
}

/* returns true if c is in the range 'A' -'Z', false otherwise */
Boolean char_isUpperCase(char c) 
{
	if(c >= UPPERCASE_START && c <= UPPERCASE_END) 
		return true;
	return false;
}

/* returns true if c is in the range '0' -'9', false otherwise */
Boolean char_isNumber(char c) 
{
	if(c >= NUMBERS_START && c <= NUMBERS_END)
		return true;
	return false;
}
/* returns true if c is an uppercase or lowercase letter, false otherwise */
Boolean char_isLetter(char c) {
	return char_isUpperCase(c) || char_isLowerCase(c); 
}
/* returns true if c is an uppercase or lowercase letter or a number, false otherwise */
Boolean char_isLetterOrNumber(char c) {
	return char_isLetter(c) || char_isNumber(c);
}

