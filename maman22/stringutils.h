/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 25/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H
 
#include "string.h"

/* --- CONSTANTS ------------------------------------------ */

#define NUMBERS_START ('0')
#define NUMBERS_END ('9')
#define UPPERCASE_START ('A')
#define UPPERCASE_END ('Z')
#define LOWERCASE_START ('a')
#define LOWERCASE_END ('z')
#define WHITESPACES_ARR_LEN (5)
const char WHITESPACES_ARR[] = {' ', '\t', '\r', '\n', '\v'};

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef char *String;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns true if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, false otherwise */
Boolean isWhitespace(char c); 
/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
Boolean isLowerCase(char c);
/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
Boolean isUpperCase(char c);
/* returns 1 if c is in the range '0' -'9', 0 otherwise */
Boolean isNumber(char c);

/* 
returns the a new string, equivilant to  the argument string s,
with all leading and trailing whitespace characters reoved 
*/
String string_Trim(const String s);

/* 
places an array of strings to "out" parameter, where each element is 
a sdubstring of s, split by the deliminator, 
and returns the number of elements in the array.
*/
int string_split(const String s, char deliminator, String out);


#endif