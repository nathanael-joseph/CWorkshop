/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef MORETYPES_H
#define MORETYPES_H

#include <limits.h>

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef enum {
	false,
	true
} Boolean;

typedef char *String;

typedef unsigned char Byte;

# if INT_MAX == +2147483647
	typedef int int32_t;
# else
	/* C standard ensures long int is at least 32 bits */
	typedef long int int32_t;
# endif

# if UINT_MAX == 4294967295
	typedef unsigned int uint32_t;
# else
	/* C standard ensures long int is at least 32 bits */
	typedef long unsigned int uint32_t;
# endif

typedef uint32_t Word;

#endif