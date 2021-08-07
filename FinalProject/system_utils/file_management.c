/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 02/06/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include <string.h>
#include "file_management.h"
#include "assembler_state.h"

/* --- FUNCTION DEFINITIONS ------------------------------ */

/* 
	Returns the next line from the file, or null if EOF has been reached.
	This is a static string, does not need to be created or freed 
*/
String fm_readLine(FILE *filePtr) {
	static char line[MAX_LINE_LEN];
	
	return fgets(line,MAX_LINE_LEN,filePtr);
}

/* 
	Returns a file pointer for writing. 
	Returns null if an error occurred and prints an errormessage
*/
FILE *fm_createFile(String filename) {
	FILE *filePtr;
	filePtr = fopen(filename, "w"); /* If the file does not exist it will be created */

	if (filePtr == NULL) {
		char msg[256];
		sprintf(msg, "The file '%s' could not be created", filename);
		el_logSystemError(msg, FATAL);
		AssemblerState_addFatalError();
	}

	return filePtr;
}

/* Writes a byte to the file. Returns true if successfull, false otherwise. */
Boolean fm_tryWriteByte(FILE *filePtr, Byte byte) {
	
	if(fputc(byte, filePtr) == EOF) {
		return false;
	} 

	return true;
}

/* Returns true if a filename has the '.asm' extension, false otherwise */
Boolean fm_isValidAssemblyFileName(String filename) {
	int len = strlen(filename);
	if(len > 4) {
		if(String_equals(filename + len - 3, ".as")) {
			return true;
		}
	}

	return false;
}