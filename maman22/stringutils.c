/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 25/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "stringutils.h"

/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* 
returns the a new string, equivilant to  the argument string s,
with all leading and trailing whitespace characters reoved 
*/
String string_Trim(const String s) {
	int len = strlen(s);
	int left = 0;
	int right = len - 1;

	String result; 

	while(start < len && isWhitespace(s[left]))
		left++;
	while(right > 0  && isWhitespace(s[right]))
		right--;

	result = calloc(sizeof(*result), right - left + 2);

	/* TODO */

	return result;


}

/* TODO - change these function names to reflect that they are for Char only, not strings */

/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, 0 otherwise */
Boolean isWhitespace(char c) {
	int i;
	for( i = 0; i < WHITESPACES_ARR_LEN; i++) {
		if (c == WHITESPACES_ARR[i])
			return true;
	}
	return false;
}

/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
Boolean isLowerCase(char c) {
	if(c >= LOWERCASE_START && c <= LOWERCASE_END) 
		return true;
	return false;
}

/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
Boolean isUpperCase(char c) 
{
	if(c >= UPPERCASE_START && c <= UPPERCASE_END) 
		return true;
	return false;
}

/* returns 1 if c is in the range '0' -'9', 0 otherwise */
Boolean isNumber(char c) 
{
	if(c >= NUMBERS_START && c <= NUMBERS_END)
		return true;
	return false;
}