/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 28/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef ASSEMBLER_STATE_H
#define ASSEMBLER_STATE_H

#include <stdio.h>
#include <stdlib.h>
#include "more_types.h"
#include "system_utils/memory_management.h"
#include "system_utils/error_logging.h"
#include "system_utils/file_management.h"
#include "datastructures/linkedlist_buffer.h"
#include "label.h"
#include "instruction.h"
#include "directive.h"

/* --- CONSTANTS ------------------------------------------ */

#define CODESEGMENT_START_ADDRESS 	(100)
#define LABEL_DICTIONARY_INIT_SIZE 	(32) 
#define MEMORY_SIZE  				(33554432) /* (2^25) = 33554432 */

/* --- FUNCTION DECLARATIONS ------------------------------ */

/* Initiates the Assembler's state */
void AssemblerState_init();
/* Sets up the state for the first file */
void AssemblerState_set(String filename);
/* Resets the state for a new file */
void AssemblerState_reset(String filename);
/* Frees the Assembler's state */
void AssemblerState_free();
/* resets file pointer to beginning of file, calculates segment sizes, etc. */
void AssemblerState_finalizeFirstPass();
/* Returns pointer to the current label dictionary */
void *AssemblerState_getLabelDictionary();
/* Returns pointer to the instruction dictionary */
void *AssemblerState_getInstructionDisctionary();
/* Returns pointer to the directive dictionary */
void *AssemblerState_getDirectiveDisctionary();
/* Increments the current line numberin the state, and returns the new value */ 
uint32_t AssemblerState_incrementLineNumber();
/* Returns the current line number in the state */ 
uint32_t AssemblerState_getLineNumber();
/* returns the current code segment address */
uint32_t AssemblerState_getCurrentCodeSegmentAddress();
/* returns the current data segment address */
uint32_t AssemblerState_getCurrentDataSegmentAddress();
/* adds 4 to the current code segment address */
void AssemblerState_incrementCurrentCodeSegmentAddress();
/* adds argument amount to current data segment address */
void AssemblerState_incrementCurrentDataSegmentAddress(uint32_t amount);
/* returns the code segment size */
uint32_t AssemblerState_getCodeSegmentSize();
/* returns the data segment size */
uint32_t AssemblerState_getDataSegmentSize();
/* Returns the name of the current state's file */
String AssemblerState_getFileName();
/* Returns the current state's file pointer */
FILE *AssemblerState_getFile();
/* Sets the state's hasFatalError flag to true */
void AssemblerState_addFatalError();
/* Returns true if a fatal error has been added to the state, false otherwise */
Boolean AssemblerState_hasFatalError();
/* Initiates the linkedlist file buffers. */
void AssemblerState_initFileBuffers();
/* writes a byte to the Code segment linked list buffer */
void AssemblerState_writeByteToCodeSegmentBuffer(Byte byte);
/* writes a byte to the Data segment linked list buffer */
void AssemblerState_writeByteToDataSegmentBuffer(Byte byte);
/* writes a formatted line in the entry file buffer using state properties and argumeent label */
void AssemblerState_writeLabelToEntryFileBuffer(String label, uint32_t absoluteAddress);
/* writes a formatted line in the extern file buffer using state properties and argumeent label */
void AssemblerState_writeLabelToExternFileBuffer(String label);
/* returns the code segment's linked list buffer */
void *AssemblerState_getCodeSegmentBuffer();
/* returns the data segment's linked list buffer */
void *AssemblerState_getDataSegmentBuffer();
/* returns the entry file's linked list buffer */
void *AssemblerState_getEntryFileBuffer();
/* returns the extern file's linked list buffer */
void *AssemblerState_getExternFileBuffer();


#endif
