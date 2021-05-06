/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef MYSET_H
#define MYSET_H

#include <stdio.h>
#include "moretypes.h"
#include "stringutils.h"
#include "set.h"
#include "errormanagement.h"

/* --- CONSTANTS ------------------------------------------ */

#define MAX_LINE_LENGTH (2048)

/* set names */
#define SETA ("SETA")
#define SETB ("SETB")
#define SETC ("SETC")
#define SETD ("SETD")
#define SETE ("SETE")
#define SETF ("SETF")

/* function names */
#define READ_SET ("read_set")
#define PRINT_SET ("print_set")
#define UNION_SET ("union_set")
#define INTERSECT_SET ("intersect_set")
#define SUB_SET ("sub_set")
#define SYMDIFF_SET ("symdiff_set")

/* --- TYPE DEFINITIONS ----------------------------------- */

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* returns a pointer to the set with the specified name,
or null if the set name does not exist */
Set *getSet(String name);

/* Returns a pointer to the next line in stdin, without 
the ending '\n' character, or null if there are no more lines
to read. Exits if a line is too long.
Memory safe - no malloc/free required.
*/
String readLine();

#endif