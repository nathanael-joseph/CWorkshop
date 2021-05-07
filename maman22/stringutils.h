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

#include <stdio.h>  /* remove this later */
#include <string.h>
#include <stdlib.h>
#include "moretypes.h"
#include "memorymanagement.h"
#include "charutils.h"


/* --- CONSTANTS ------------------------------------------ */


/* --- TYPE DEFINITIONS ----------------------------------- */



/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns true if the the strings a and b are equivilant, false otherwise */
Boolean string_equals(const String a, const String b);

/* Parses the string for an integer, and returns true if successfull, 
false otherwaise */
Boolean string_tryParseInt(const String s, int *out);

/* 
returns the a new string, equivilant to  the argument string s,
with all leading and trailing whitespace characters reoved 
*/
String string_trim(const String s);

/* 
Places an array of strings to "out" parameter, where each element is 
a substring of s, split by the deliminator and then trimmed.
Returns the number of elements in the array.
*/
int string_split(const String s, char deliminator, String **out);


#endif