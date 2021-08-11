/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 03/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string.h>
#include <stdlib.h>
#include "more_types.h"
#include "system_utils/memory_management.h"
#include "type_utils/char_utils.h"
#include "bounds.h"


/* --- CONSTANTS ------------------------------------------ */

#define PRIMARY_HASH_CONST (31)

/* --- TYPE DEFINITIONS ----------------------------------- */



/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns true if the the strings a and b are equivilant, false otherwise */
Boolean String_equals(const String a, const String b);

/* Parses the string for an integer, and returns true if successfull, 
false otherwaise -- DEPRECIATED - USE tryParseInt32 */
Boolean String_tryParseInt(const String s, int *out);

/* Parses the string for an integer, and returns true if successfull, 
false otherwaise - returns false also in case of overflow */
Boolean String_tryParseInt32(const String s, int32_t *out);

/* 
returns the a new string, equivilant to  the argument string s,
with all leading and trailing whitespace characters reoved 
*/
String String_trim(const String s);

/* 
Places an array of strings to "out" parameter, where each element is 
a substring of s, split by the deliminator and then trimmed.
Returns the number of elements in the array.
*/
int String_split(const String s, char deliminator, String **out);

/* 
	Gets gets hash number in the range [0, M-1] for the argument String.
	
	Hash: Rolling polynomial 
		(s[0]P^0 + s[1]P^1 + ... + s[n-1]P^(n-1)) % M
		P = 31, M = argument M

	This is not a cryptographic hash function - use only for hashtables etc.
*/
unsigned int String_hash(const String str, unsigned int M); 

#endif