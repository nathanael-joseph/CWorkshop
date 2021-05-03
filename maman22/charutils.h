/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 03/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef CHARUTILS_H
#define CHARUTILS_H

#include "boolean.h"


/* --- CONSTANTS ------------------------------------------ */

#define NULL_CHAR ('\0')
#define NUMBERS_START ('0')
#define NUMBERS_END ('9')
#define UPPERCASE_START ('A')
#define UPPERCASE_END ('Z')
#define LOWERCASE_START ('a')
#define LOWERCASE_END ('z')
#define WHITESPACES_ARR_LEN (5)
const char WHITESPACES_ARR[WHITESPACES_ARR_LEN];


/* --- TYPE DEFINITIONS ----------------------------------- */

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns true if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, false otherwise */
Boolean char_isWhitespace(char c); 
/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
Boolean char_isLowerCase(char c);
/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
Boolean char_isUpperCase(char c);
/* returns 1 if c is in the range '0' -'9', 0 otherwise */
Boolean char_isNumber(char c);

#endif