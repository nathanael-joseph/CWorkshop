/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 28/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "more_types.h"
#include "system_utils/memory_management.h"
#include "system_utils/error_logging.h"
#include "system_utils/file_management.h"
#include "type_utils/string_utils.h"
#include "datastructures/dictionary.h"
#include "assembler_state.h"
#include "label.h"
#include "bounds.h"

/* --- CONSTANTS ------------------------------------------ */

#define INSTRUCTIONS_CSV_FILENAME ("assembler_instructions.csv")


/* --- TYPE DEFINITIONS ----------------------------------- */

typedef void (*ValidateArgsFnct)(String args);
typedef void (*EncodeFnct)(void *instructionData, String args);

typedef enum {
	R = 0,	/* R - Register instructions */
	I = 1,	/* I - Immediate instructions */
	J = 2	/* J - Jump instructions */
} InstructionType;

typedef struct { 
	/* String name; -- will be stored as the key */
	InstructionType type;
	int opCode;
	int functCode;
	ValidateArgsFnct validateArgs; 
	EncodeFnct encode;
} InstructionData;

typedef enum {
	R_1 = 1,
	R_2 = 2
} R_InstructionSubtype;

typedef enum {
	I_1 = 1,
	I_2 = 2,
	I_3 = 3
} I_InstructionSubtype;

typedef enum {
	J_1 = 1,
	J_2 = 2,
	J_3 = 3
} J_InstructionSubtype;



/* --- FUNCTION DECLARATIONS ------------------------------ */

/* creates and populates the instruction dictionary for the assembler state */
void *Instruction_getInstructionDictionary();

/* creates a new instruction data instance */
void *InstructionData_init();
/* frees an instruction data instance */
void InstructionData_free(void *instructionData);


#endif