/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 02/06/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <stdio.h>
#include "more_types.h"
#include "system_utils/error_logging.h"

/* --- CONSTANTS ------------------------------------------ */

#define MAX_LINE_LEN (256)

/* --- TYPE DEFINITIONS ----------------------------------- */

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* Returns the next line from the file. This is a static string, does not need to be created or freed */
String fm_readLine(FILE *filePtr);

/* 
	Returns a file pointer for writing. If the operation is unsuccessfull,
	an error message will be logged.
*/
FILE *fm_createFile(String filename);

/* Writes a byte to the file. Returns true if successfull, false otherwise. */
Boolean fm_tryWriteByte(FILE *filePtr, unsigned char byte);

/* Returns true if a filename has the '.asm' extension, false otherwise */
Boolean fm_isValidAssemblyFileName(String filename);

#endif
