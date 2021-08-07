/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 28/07/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "directive.h"


/* --- STATIC FUNCTION DECLARATIONS ---------------------- */

/* 
	All _validateArgsAndApply functions are responsible for performing
	the first pass actions for that particular directive:
	- validating syntax and arguments.
	- printing error messages.
	- setting fatal error flag if need be.
	- updating the label dictionary with attributes.
	- incrementing the state's data segment address pointer
*/ 

static void DB_validateArgsAndApply(String args);
static void DH_validateArgsAndApply(String args);
static void DW_validateArgsAndApply(String args);
static void ASCIZ_validateArgsAndApply(String args);

static void ENTRY_validateArgsAndApply(String args);
static void EXTERN_validateArgsAndApply(String args);


/* 
	All _encode functions are responsible for 
	- encoding the directive to the data segment buffer.
	- incrementing the state's data segment address pointer.
	these will be called in the validate and apply functions.
*/ 
static void DB_encode(String *argsArr, int argCount);
static void DH_encode(String *argsArr, int argCount);
static void DW_encode(String *argsArr, int argCount);
static void ASCIZ_encode(String argTrimmed);


/* -- helper methods -- */
/* 
	validates that at least one arg exists, and all args are integers between
	the lower bound and the upper bound. 
*/
static void D_INTEGER_validateArgs(String *argsArr,int argCount, int lowerBound, int upperBound);


/* --- STATIC FUNCTION DEFINITIONS ----------------------- */

/* -- helper methods -- */

/* 
	validates that at least one arg exists, and all args are integers between
	the lower bound and the upper bound.
*/
static void D_INTEGER_validateArgs(String *argsArr,int argCount, int lowerBound, int upperBound) {
	int i, temp;
	char msg[256];
	
	if(argCount == 0) {
		sprintf(msg,"No arguments where provided. ");
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {

		if(! String_tryParseInt(argsArr[i], &temp) ) {

			sprintf(msg,
				 	"the arg '%s' could not be parsed as an integer",
				 	argsArr[i]);

			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
		} else {
			if(temp < lowerBound || temp > upperBound) {
				sprintf(msg,
				 		"the arg '%s' is out of range",
				 		argsArr[i]);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}
		}
	}
}



/* validates all args are Byte sized integers */
static void DB_validateArgsAndApply(String args) {	
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	argCount = String_split(args, ',', &argsArr);

	D_INTEGER_validateArgs(argsArr, argCount, BYTE_L_BOUND, BYTE_U_BOUND);

	if(! AssemblerState_hasFatalError()) {
		DB_encode(argsArr, argCount);
	}

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* validates all args are half word sized integers */
static void DH_validateArgsAndApply(String args) {	
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	argCount = String_split(args, ',', &argsArr);

	D_INTEGER_validateArgs(argsArr, argCount,  HALF_L_BOUND, HALF_U_BOUND);

	if(! AssemblerState_hasFatalError()) {
		DH_encode(argsArr, argCount);
	}

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* validates all args are word sized integers */
static void DW_validateArgsAndApply(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	argCount = String_split(args, ',', &argsArr);

	D_INTEGER_validateArgs(argsArr, argCount,  WORD_L_BOUND, WORD_U_BOUND);

	if(! AssemblerState_hasFatalError()) {
		DW_encode(argsArr, argCount);
	}

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}



/* validates there is only one argument, and the argument is a correcty formatted string */
static void ASCIZ_validateArgsAndApply(String args) {

	Boolean invalidStringFlag = false;
	int i, len;
	char msg[256];
	String arg = String_trim(args);

	len = strlen(arg);
	if(len > 1 ) {

		if(arg[0] != '"' || arg[len -1] != '"') {
			invalidStringFlag = true;

		}

		for(i = 1; i < len -1; i++) {
			if(arg[i] == '"') {
				invalidStringFlag = true;
			}
		}

	} else {

		invalidStringFlag = true;
	}

	if(invalidStringFlag) {
		sprintf(msg, "'%s' is not a valid string", arg);
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}
	
	if(!AssemblerState_hasFatalError()) {
		ASCIZ_encode(arg);
	}

	free(arg);
}

/* Validate the label name, and apply the attribute if possible  */
static void ENTRY_validateArgsAndApply(String args) {
	Dictionary *labelsDict = AssemblerState_getLabelDictionary();
	String arg = String_trim(args);
	char msg[256];
	LabelData *labeldata;

	if(Label_isValidLabelName(arg)) {
		labeldata = Dictionary_getValue(labelsDict, arg);

		if(labeldata) {

			if(labeldata->scope == EXTERNAL) {
				sprintf(msg,
						 "The label '%s' cannot be marked as both .entry and .extern",
						  arg);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			} else {
				/* all is good, apply .entry attribute */
				labeldata->scope = ENTRY;
			}

		} else {
			/* new label */
			labeldata = LabelData_init();
			labeldata->scope = ENTRY;
			Dictionary_setValue(labelsDict, arg, labeldata);

		}

	} else {
		sprintf(msg, "'%s' is not a valid label name", arg);
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}
	free(arg);
}

/* Validate the label name, and apply the attribute if possible  */
static void EXTERN_validateArgsAndApply(String args) {
	Dictionary *labelsDict = AssemblerState_getLabelDictionary();
	String arg = String_trim(args);
	char msg[256];
	LabelData *labeldata;

	if(Label_isValidLabelName(arg)) {
		labeldata = Dictionary_getValue(labelsDict, arg);

		if(labeldata) {

			if(labeldata->scope == ENTRY) {
				sprintf(msg,
						 "The label '%s' cannot be marked as both .entry and .extern",
						  arg);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			} 
			else if(LabelData_hasBeenDefinedLocally(labeldata)) {
				sprintf(msg,
						 "The label '%s' has been defined in this file.",
						  arg);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}
			else {
				/* all is good, apply .extern attribute */
				labeldata->scope = EXTERNAL;
			}

		} else {
			/* new label */
			labeldata = LabelData_init();
			labeldata->scope = EXTERNAL;
			Dictionary_setValue(labelsDict, arg, labeldata );
		}

	} else {
		sprintf(msg, "'%s' is not a valid label name", arg);
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}	

	free(arg);
}


/* Writes a series of bytes to the data segment buffer */
static void DB_encode(String *argsArr, int argCount) {
	int i, temp;
	Byte byte;

	for(i = 0; i < argCount; i++) {
		String_tryParseInt(argsArr[i], &temp);
		byte = temp;
		AssemblerState_writeByteToDataSegmentBuffer(byte);
	}
}

/* Writes a series of half words to the data segment buffer in little endian format */
static void DH_encode(String *argsArr, int argCount) {
	int i, temp;
	Byte byte;

	for(i = 0; i < argCount; i++) {
		String_tryParseInt(argsArr[i], &temp);

		byte = temp;
		AssemblerState_writeByteToDataSegmentBuffer(byte);
		byte = temp >> 8;
		AssemblerState_writeByteToDataSegmentBuffer(byte);
	}

}

/* Writes a series of words to the data segment buffer in little endian format */
static void DW_encode(String *argsArr, int argCount) {
	int i, j, temp;
	Byte byte;

	for(i = 0; i < argCount; i++) {
		String_tryParseInt(argsArr[i], &temp);
		
		for(j=0; j < 32; j += 8) {
			byte = (temp >> j);
			AssemblerState_writeByteToDataSegmentBuffer(byte);
		}
	}

}

/* Writes a series of chars to the data segment buffer, and appends a 0 byte at the end */
static void ASCIZ_encode(String argTrimmed) {
	Byte byte;
	int i;

	/* first and last characters are  '"' */
	for(i = 1; i < strlen(argTrimmed) - 1; i++) {
		byte = argTrimmed[i];
		AssemblerState_writeByteToDataSegmentBuffer(byte);
	}

	AssemblerState_writeByteToDataSegmentBuffer('\0');
}


/* --- FUNCTION DEFINITIONS ------------------------------ */

/* creates a new instruction data instance */
void *DirectiveData_init(DirectiveType type, ValidateArgsAndApplyFnct validateArgsAndApply) {
	DirectiveData *directiveData = malloc(sizeof(*directiveData));
	directiveData->type = type;
	directiveData->validateArgsAndApply = validateArgsAndApply;
	return directiveData;
}
/* frees an instruction data instance */
void DirectiveData_free(void *directiveData) {
	free(directiveData);
}
/* creates and populates the directive dictionary for the assembler state */
void *Directive_getDirectiveDictionary() {
	Dictionary *directiveDict = Dictionary_init(6);

	Dictionary_setValue(directiveDict,
						"db",
						DirectiveData_init(D, DB_validateArgsAndApply)
						);

	Dictionary_setValue(directiveDict,
						"dh",
						DirectiveData_init(D, DH_validateArgsAndApply)
						);

	Dictionary_setValue(directiveDict,
						"dw",
						DirectiveData_init(D, DW_validateArgsAndApply)
						);

	Dictionary_setValue(directiveDict,
						"asciz",
						DirectiveData_init(D, ASCIZ_validateArgsAndApply)
						);

	Dictionary_setValue(directiveDict,
						"entry",
						DirectiveData_init(A, ENTRY_validateArgsAndApply)
						);

	Dictionary_setValue(directiveDict,
						"extern",
						DirectiveData_init(A, EXTERN_validateArgsAndApply)
						);

	return directiveDict;
}
