/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/03/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 11 Question 1
-------------------------------------------------------------------------------
*/

#include <stdio.h>

/* --- CONSTANTS ------------------------------------------ */
#define NUMBERS_START ('0')
#define NUMBERS_END ('9')
#define UPPERCASE_START ('A')
#define UPPERCASE_END ('Z')
#define LOWERCASE_START ('a')
#define LOWERCASE_END ('z')
#define FULLSTOP ('.')
#define DOUBLEQUOTE ('"')
#define WHITESPACES_ARR_LEN (5)
const char WHITESPACES_ARR[] = {' ', '\t', '\r', '\n', '\v'};


/* --- FUNCTION DECLARATIONS -------------------------------- */


/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, 0 otherwise */
int isWhitespace(char c); 
/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
int isLowerCase(char c);
/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
int isUpperCase(char c);
/* returns 1 if c is in the range '0' -'9', 0 otherwise */
int isNumber(char c);


/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
char toLower(char c);
/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
char toUpper(char c);


/* flips an int flag from 1 to 0, or from 0 to 1 */
void flipFlag(int* flag);
/* sets an int flag to 1 */
void setFlag(int* flag);
/* sets an int flag to 0 */
void clearFlag(int* flag);