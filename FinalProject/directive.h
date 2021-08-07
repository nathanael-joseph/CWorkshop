/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 31/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include "more_types.h"
#include "system_utils/memory_management.h"
#include "system_utils/error_logging.h"
#include "type_utils/string_utils.h"
#include "assembler_state.h"
#include "label.h"
#include "bounds.h"

/* --- CONSTANTS ------------------------------------------ */


/* --- TYPE DEFINITIONS ----------------------------------- */

typedef void (*ValidateArgsAndApplyFnct)(String args);

typedef enum {
	D = 0,	/* D - Data Directive .dw .dh etc. */
	A = 1 	/* A - Label Attribute Directive .entry .extern */
} DirectiveType;

typedef struct { 
	DirectiveType type;
	ValidateArgsAndApplyFnct validateArgsAndApply; 
} DirectiveData;



/* --- FUNCTION DECLARATIONS ------------------------------ */

/* creates and populates the directive dictionary for the assembler state */
void *Directive_getDirectiveDictionary();

/* creates a new instruction data instance */
void *DirectiveData_init(DirectiveType type, ValidateArgsAndApplyFnct validateArgsAndApply);
/* frees an instruction data instance */
void DirectiveData_free(void *directiveData);

#endif