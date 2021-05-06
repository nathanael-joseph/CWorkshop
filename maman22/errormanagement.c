/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/05/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "errormanagement.h"


/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* Prints an error message to stderr, and exits the program. */
void em_throwMemoryAllocationErorr() {
	fputs("A memory allocation Error occured... \nExiting... \n", stderr);
	exit(MEM_ALLOC_ERR);
}
/* Prints an error message to stderr, does not exit */
void em_throwInvalidArgumentError(String argument) {
	fprintf(stderr, "[%s] is not a valid argument. \nSkipping statement... \n", argument);
}
/* Prints an error message to stderr, does not exit */
void em_throwInvalidFunctionError(String function) {
	fprintf(stderr, "[%s] is not a recognised function. \nSkipping statement... \n", function);	
}
/* Prints an error message to stderr, does not exit */
void em_throwArgumentOutOfRangeError(String argument) {
	fprintf(stderr, "[%s] is out of range. \nSkipping statement... \n", argument);
}
/* Prints an error message to stderr, does not exit */
void em_throwInvalidFunctionTerminationError() {
	fputs("The terminating argument [-1] is missing. \nSkipping statement... \n", stderr);
}
/* Prints an error message to stderr, and exits the program. */
void em_throwInvalidTerminationError() {
	fputs("End of file reached, with no STOP command \nExiting... \n", stderr);
	exit(INV_TERMINATION_ERR);
}
