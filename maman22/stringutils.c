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

/* returns true if the the strings a and b are equivilant, false otherwise */
Boolean string_equals(const String a, const String b) {
	return !strcmp(a,b);
}

/* Parses the string for an integer, and returns true if successfull, 
false otherwaise */
Boolean string_tryParseInt(const String s, int *out) {

	String trimmed_s;
	int result, sign, i;

	result = 0; sign = 1; i = 0;
	trimmed_s = string_trim(s);

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
Places an array of strings to "out" parameter, where each element is 
a substring of s, split by the deliminator and then trimmed.
Returns the number of elements in the array.
*/
int string_split(const String s, char deliminator, String **out) {

	int delimCounter = 0;
	int i, j, k;
	String temp = calloc(1, sizeof(*temp));

	for(i = 0; i < strlen(s); i++) {
		if (s[i] == deliminator) {
			delimCounter++;
		}
	}

	*out = calloc(delimCounter + 1, sizeof(**out));

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

	result = calloc(resultLength + 1, sizeof(*result));
	result = strncpy(result, s + left, resultLength);

	return result;
}
