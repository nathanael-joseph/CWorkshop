/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 08/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef ERROR_LOGGING_H
#define ERROR_LOGGING_H

#include <stdio.h>
#include "more_types.h"
#include "assembler_state.h"

/* --- CONSTANTS ------------------------------------------ */


#define ANSI_COLOUR_BLACK  		"\033[30;22m"
#define ANSI_COLOUR_RED  		"\033[91;22m"
#define ANSI_COLOUR_GREEN  		"\033[32;22m"
#define ANSI_COLOUR_YELLOW  	"\033[33;22m"
#define ANSI_COLOUR_BLUE  		"\033[94;22m"
#define ANSI_COLOUR_MAGENTA 	"\033[35;22m"
#define ANSI_COLOUR_CYAN  		"\033[36;22m"
#define ANSI_COLOUR_WHITE  		"\033[37;22m"

#define ANSI_COLOUR_BLACK_B  	"\033[30;1m"
#define ANSI_COLOUR_RED_B  		"\033[91;1m"
#define ANSI_COLOUR_GREEN_B  	"\033[32;1m"
#define ANSI_COLOUR_YELLOW_B 	"\033[33;1m"
#define ANSI_COLOUR_BLUE_B 		"\033[94;1m"
#define ANSI_COLOUR_MAGENTA_B 	"\033[35;1m"
#define ANSI_COLOUR_CYAN_B  	"\033[36;1m"
#define ANSI_COLOUR_WHITE_B  	"\033[37;1m"

#define ANSI_COLOUR_RESET 		"\033[0m"

#define ERROR_STREAM (stdout)	/* as requested in the brief, error messages to stdout, not stderr */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef enum {
	INFO = 0,
	WARNING = 1,
	FATAL = 2
} ErrorLevel;

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* prints a formatted error message to stdout. */
void el_logAssemblyError(String msg, ErrorLevel level, String filename, int linenumber);

/* prints a formatted error message to stdout, gets lineNumber and filename directly from state */
void el_logAssemblyErrorDefault(String msg, ErrorLevel level);

/* prints a formatted error message to stdout without linenumber and filename */
void el_logSystemError(String msg, ErrorLevel level);

#endif
