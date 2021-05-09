/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 08/05/2021
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
#define SET_LBOUND (1)
#define SET_UBOUND (128) 

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
#define STOP ("stop")

/* --- TYPE DEFINITIONS ----------------------------------- */

/* pointer to a function that takes two pointers as arguments,
and returns a Set pointer */
typedef Set *(*SetArithmaticFunctionPtr)(void * , void *);


/* --- FUNCTION DECLARATIONS ------------------------------ */

/* Parses the line of text, and executes the command if possible,
else prints an error massage */
void executeLine(String line, Boolean *stop);
/* Parses the function arguments from the String CSV and 
executes read_set if possible, else prints an error message */
void executeReadSet(String argsCSV);
/* Parses the function arguments from the String CSV and 
executes print_set if possible, else prints an error message */
void executePrintSet(String argsCSV);
/* Parses the function arguments from the String CSV and 
executes the arithmatic function passed if possible, 
else prints an error message */
void executeSetArithmatic(String argsCSV, SetArithmaticFunctionPtr fptr);


/* returns a pointer to the set with the specified name,
or null if the set name does not exist */
Set *getSet(String name);

/* Returns a pointer to the next line in stdin, without 
the ending '\n' character, or null if there are no more lines
to read. Exits if a line is too long.
Memory safe - no malloc/free required.
*/
String readLine();

/* prints the contents of the set to stdin, or "set is empty" */
void printSet(void *set);

#endif