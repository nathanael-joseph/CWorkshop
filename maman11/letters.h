#include <stdio.h>

/* --- CONSTANTS ------------------------------------------ */
#define NUMBERS_START ('0')
#define NUMBERS_END ('9')
#define UPPERCASE_START ('A')
#define UPPERCASE_END ('Z')
#define LOWERCASE_START ('a')
#define LOWERCASE_END ('z')
#define WHITESPACES_ARR_LEN (5)
#define FULLSTOP ('.')
#define DOUBLEQUOTE ('"')
const char WHITESPACES_ARR[] = {' ', '\t', '\r', '\n', '\v'};

/* --- FUNCTION DEFINITIONS -------------------------------- */
/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'} 0 otherwise */
short int isWhitespace(char c); 

/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
short int isLowerCase(char c);

/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
short int isUpperCase(char c);

/* returns 1 if c is in the range '0' -'9', 0 otherwise */
short int isNumber(char c);