/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 04/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "stringutils.h"

/* --- FUNCTION DEFINITIONS ----------------------------------------- */

Boolean string_tryParseInt(const String s, int *out) {
	/* TODO */

	int result, sign, i;
	result = 0; sign = 1; i = 0;
	String trimmed_s = string_trim(s);

	if (! char_isNumber(trimmed_s[i])) {
		if (trimmed_s[i++] == '-') {
			sign = -1;
		}
		else {
			return false;
		}
	} 

	while(i < strlen(trimmed_s)) {
		if (! char_isNumber(trimmed_s[i])) {
			return false;
		}
		else {
			result *= 10;
			result += trimmed_s[i] - NUMBERS_START;
		}

		 i++;
	}

	free(trimmed_s);

	*out = sign * result;

	return true;
}

/* 
places an array of strings to "out" parameter, where each element is 
a sdubstring of s, split by the deliminator, 
and returns the number of elements in the array.
*/
int string_split(const String s, char deliminator, String **out) {

	int delimCounter = 0;
	int i, j, k;
	String temp = calloc(sizeof(*temp),1);

	for(i = 0; i < strlen(s); i++) {
		if (s[i] == deliminator) {
			delimCounter++;
		}
	}

	*out = calloc(sizeof(**out), delimCounter + 1);

	/*	i = index of deliminator, 
		j = beginning of substring, 
		k = index of out array 
	*/ 
	for(i = 0, j = 0, k = 0; i < strlen(s); i++) {
		if (s[i] == deliminator) {
			temp = realloc(temp, i-j + 1);
			temp[i-j] = NULL_CHAR; /* terminate string */
			temp = strncpy(temp, s + j, i - j);
			(*out)[k++] = string_trim(temp); /* trim calls malloc internally */
			j = i + 1;
		}
	}

	temp = realloc(temp, i-j + 1);
	temp[i-j] = NULL_CHAR; /* terminate string */
	temp = strncpy(temp, s + j, i - j);
	(*out)[k++] = string_trim(temp); /* trim calls malloc internally */

	free(temp);

	return k;
}



/* 
returns the a new string, equivilant to  the argument string s,
with all leading and trailing whitespace characters reoved 
*/
String string_trim(const String s) {
	int len = strlen(s);
	int left = 0;
	int right = len - 1;
	int resultLength;

	String result; 

	while(left < len && char_isWhitespace(s[left]))
		left++;
	while(right > left  && char_isWhitespace(s[right]))
		right--;

	resultLength = right - left + 1;

	result = calloc(sizeof(*result), resultLength + 1);
	result = strncpy(result, s + left, resultLength);

	return result;
}
