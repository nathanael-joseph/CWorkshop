/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#ifndef ERRORMANAGEMENT_H
#define ERRORMANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include "moretypes.h"


/* --- CONSTANTS ------------------------------------------ */

#define MEM_ALLOC_ERR (-1)
#define INV_TERMINATION_ERR (-2)


/* --- TYPE DEFINITIONS ----------------------------------- */

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* Prints an error message to stderr, and exits the program. */
void em_throwMemoryAllocationErorr();
/* Prints an error message to stderr, does not exit */
void em_throwInvalidArgumentError(String argumentName);
/* Prints an error message to stderr, does not exit */
void em_throwInvalidFunctionError(String functionName);
/* Prints an error message to stderr, does not exit */
void em_throwArgumentOutOfRangeError(String argument);
/* Prints an error message to stderr, does not exit */
void em_throwInvalidFunctionTerminationError();
/* Prints an error message to stderr, and exits the program. */
void em_throwInvalidTerminationError();


#endif