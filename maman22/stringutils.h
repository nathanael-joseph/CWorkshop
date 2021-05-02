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
/* --- TYPE DEFINITIONS ----------------------------------- */

typedef *char String;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* 
returns the argument string s with all leading and 
trailing whitespace characters reoved 
*/
String string_Trim(String s);

/* 
returns an array of strings, where each element is 
a sdubstring of s, split by the deliminator
*/
String *string_split(String s, char deliminator);


#endif