/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 08/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "error_logging.h"

/* --- FUNCTION DEFINITIONS ------------------------------ */

/* prints a formatted error message to stdout. */
void el_logAssemblyError(String msg, ErrorLevel level, String filename, int linenumber) {
	switch(level) {
		case INFO:
			fprintf(ERROR_STREAM, 
					"%s%s line %d - INFO: %s\n %s\n",
					ANSI_COLOUR_BLUE_B,
					filename,
					linenumber,
					ANSI_COLOUR_RESET,
					msg
					);
			break;
		case WARNING:
			fprintf(ERROR_STREAM, 
					"%s%s line %d - WARNING: %s\n %s\n",
					ANSI_COLOUR_YELLOW_B,
					filename,
					linenumber,			
					ANSI_COLOUR_RESET,
					msg
					);
			break;
		case FATAL:
			fprintf(ERROR_STREAM, 
					"%s%s line %d - FATAL: %s\n %s\n",
					ANSI_COLOUR_RED_B,
					filename,
					linenumber,					
					ANSI_COLOUR_RESET,
					msg
					);
			break;
	}
}

/* prints a formatted error message to stdout, gets lineNumber and filename directly from state */
void el_logAssemblyErrorDefault(String msg, ErrorLevel level) {
	el_logAssemblyError(msg, 
						level, 
						AssemblerState_getFileName(), 
						AssemblerState_getLineNumber()
						);
}

/* prints a formatted error message to stdout, without line number and filename */
void el_logSystemError(String msg, ErrorLevel level) {
	switch(level) {
		case INFO:
			fprintf(ERROR_STREAM, 
					"%s INFO: %s\n %s\n",
					ANSI_COLOUR_BLUE_B,
					ANSI_COLOUR_RESET,
					msg
					);
			break;
		case WARNING:
			fprintf(ERROR_STREAM, 
					"%s WARNING: %s\n %s\n",
					ANSI_COLOUR_YELLOW_B,	
					ANSI_COLOUR_RESET,
					msg
					);
			break;
		case FATAL:
			fprintf(ERROR_STREAM, 
					"%s FATAL: %s\n %s\n",
					ANSI_COLOUR_RED_B,				
					ANSI_COLOUR_RESET,
					msg
					);
			break;
	}
}