/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef LABEL_H
#define LABEL_H

#include "more_types.h"
#include "system_utils/memory_management.h"
#include "assembler_state.h"

/* --- TYPE DEFINITIONS ----------------------------------- */

/* enum for which segment the label refers to */
typedef enum {
	CODE = 0,
	DATA = 1,
	UNDEFINED = 2 /* defualt value */
} LabelType;

typedef enum {
	LOCAL = 0, /* default value if not specified */
	ENTRY = 1,
	EXTERNAL = 2
} LabelScope;

typedef struct {
	LabelType type;
	LabelScope scope;
	int32_t segmentAddress; /* default value of -1 to check whether or not it has been defined */
} LabelData;


/* --- FUNCTION DECLARATIONS ------------------------------ */

/* creates a new labeldata instance */
LabelData *LabelData_init();
/* frees a labeldata instance */
void LabelData_free(void *labeldata);

/* 
	Returns the absolute address of a label, or -1 if it has not been defined.
	If the address is external 0 will be returned. 
*/
int32_t LabelData_getAbsoluteAddress(void *labeldata);

/* 
	returns true if the label's address has allready been defined, 
	or if it has already been marked as external
*/
Boolean LabelData_hasBeenDefinedLocally(void *labeldata);

/* Returns true if a tag name meets required format, false otherwise. */
Boolean Label_isValidLabelName(String name);

#endif