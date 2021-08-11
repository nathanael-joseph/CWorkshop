/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "instruction.h"


/* --- STATIC FUNCTION DECLARATIONS ---------------------- */

/* 
	All _validateArgs functions are responsible for performing
	the first pass actions for that particular instruction:
	- validating syntax and arguments.
	- printing error messages.
	- setting fatal error flag if need be.
*/ 
static void R_1_validateArgs(String args);
static void R_2_validateArgs(String args);

static void I_1_validateArgs(String args);
static void I_2_validateArgs(String args);
static void I_3_validateArgs(String args);

static void J_1_validateArgs(String args);
static void J_2_validateArgs(String args);
static void J_3_validateArgs(String args);

/* 
	All _encode functions are responsible for performing
	the second pass actions for that particular instruction:
	- encoding the instruction call to a word.
	- writing encoded instructions to the code buffer.
	- raising any additional errors, such as undefined labels, 
	out of range addresses etc.
*/ 

static void R_1_encode(void *instructionData, String args);
static void R_2_encode(void *instructionData, String args);

static void I_1_encode(void *instructionData, String args);
static void I_2_encode(void *instructionData, String args);
static void I_3_encode(void *instructionData, String args);

static void J_1_encode(void *instructionData, String args);
static void J_2_encode(void *instructionData, String args);
static void J_3_encode(void *instructionData, String args);

/* -- helper methods -- */

/* returns true if the string arg represents a valid register, false otherwise */
static Boolean isValidRegister(String arg);
/* 
	returns true if the string arg represents a valid signed number, 
	between -2^15 and 2^15 -1, false otherwise.
*/
static Boolean isValidImmediate(String arg);
/* returns the numeric value of the register (between 0 and 31) */
static int getRegisterNumber(String arg);
/* returns the numeric value of the immediate arg string. */
static int32_t getImmediateNumber(String arg);
/* writes a word to the assembler state's code segment buffer in little endian format */
static void writeWordToCodeSegmentBufferLittleEndian(Word word);


/* --- STATIC FUNCTION DEFINITIONS ----------------------- */

/* -- helper methods -- */

/* returns true if the string arg represents a valid register, false otherwise */
static Boolean isValidRegister(String arg) {
	int32_t regNumber, i;
	String regNumberStr;

	if(arg[0] == '$') {
		regNumberStr = (arg  + 1);
		/* ensure the arg includes only digits afgter the $ sign. */
		for(i = 0; i < strlen(regNumberStr); i++) {
			if(! char_isNumber(regNumberStr[i]) ) {
				return false;
			}
		}

		if(String_tryParseInt32(regNumberStr, &regNumber)) {
			if(0 <= regNumber && regNumber <= 31 ) {
				return true;
			}
		}
	}

	return false;
}

/* 
	returns true if the string arg represents a valid signed number, 
	between - 2^15 and 2^15 -1, false otherwise.
*/
static Boolean isValidImmediate(String arg) {
	int32_t immed;

	if(String_tryParseInt32(arg, &immed)) {
		if( HALF_L_BOUND <= immed && immed <= HALF_U_BOUND) {
			return true;
		}
	}

	return false;
}

/* returns the numeric value of the register (between 0 and 31) */
static int getRegisterNumber(String arg) {
	/* use only after validation */
	int regNumber;
	String_tryParseInt(arg + 1, &regNumber);

	return regNumber;
}

/* returns the numeric value of the immediate arg string. */
static int32_t getImmediateNumber(String arg) {
	/* use only after validation */
	int32_t immed;
	String_tryParseInt32(arg, &immed);

	return immed;
}

/* writes a word to the assembler state's code segment buffer in little endian format */
static void writeWordToCodeSegmentBufferLittleEndian(Word word) {
	int i;
	Byte byte;

	for(i = 0; i < 32; i += 8 ) {
		byte = (word >> i);
		AssemblerState_writeByteToCodeSegmentBuffer(byte);
	}
}


/* -- validateArgs methods -- */

/* validate all args are registers, and there are 3 args */
static void R_1_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 3) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 3, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {

		if(i < 3 && !isValidRegister(argsArr[i])) {
		
			sprintf(msg, "The argument '%s' is not a valid register", argsArr[i]);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();

		}
		free(argsArr[i]);
	}
	free(argsArr);
}

/* validate all args are registers, and there are 2 args */
static void R_2_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 2) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 2, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {

		if(i < 3 && !isValidRegister(argsArr[i])) {	
			sprintf(msg, "The argument '%s' is not valid", argsArr[i]);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
		}

		free(argsArr[i]);
	}
	free(argsArr);
}

/* validates there are 3 args, first and last are valid registers, and second is valid immediate */
static void I_1_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 3) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 3, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {

		if(i == 1) {

			if(! isValidImmediate(argsArr[i])) {
				sprintf(msg, "The argument '%s' is not a valid immediate", argsArr[i]);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}

		} else if (i < 3) {

			if(! isValidRegister(argsArr[i])) {
				sprintf(msg, "The argument '%s' is not a valid register", argsArr[i]);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}
		}

		free(argsArr[i]);
	}
	free(argsArr);
}

/* validates first two arguments are registers and third is a valid label name */
static void I_2_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 3) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 3, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {

		if(i == 2) {

			if(! Label_isValidLabelName(argsArr[i])) {
				sprintf(msg, "The argument '%s' is not a valid label name", argsArr[i]);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}

		} else if (i < 3) {

			if(! isValidRegister(argsArr[i])) {
				sprintf(msg, "The argument '%s' is not a valid register", argsArr[i]);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}
		}

		free(argsArr[i]);
	}
	free(argsArr);
}

/* validation rules for I_3 are the same as I_1 */
static void I_3_validateArgs(String args) {
	I_1_validateArgs(args);
}

/* validates there is only one arg, and it is either a register or a label */
static void J_1_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 1) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 1, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	if(! (Label_isValidLabelName(argsArr[0]) || isValidRegister(argsArr[0])) ) {
		sprintf(msg,
			 	"The argument '%s' is not a valid register or label ",
			 	argsArr[0]);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);

}

/* validates that there is a single argument, and the argument is a label */
static void J_2_validateArgs(String args) {
	int argCount, i;
	String *argsArr; /* will be allocated by String_split, requires freeing */
	char msg[256];

	argCount = String_split(args, ',', &argsArr);
	
	if(argCount != 1) {

		sprintf(msg,
			 	"An Invalid number of arguments where provided. Expected 1, got %d ",
			 	argCount);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	if(! Label_isValidLabelName(argsArr[0])) {
		sprintf(msg,
			 	"The argument '%s' is not a valid label ",
			 	argsArr[0]);

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* Validates that there are no args */
static void J_3_validateArgs(String args) {
	String arg = String_trim(args); /* requires freeing */
	char msg[256];
	
	if(strlen(arg) > 0) {

		sprintf(msg,
			 	"The stop instruction takes no arguments");

		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
	}

	free(arg);
}


/* -- encode methods -- */

/* Writes a word to the code segment buffer encoding the R_1 instruction call */
static void R_1_encode(void *instructionData, String args) {
	InstructionData *ins = instructionData;
	String *argsArr;
	int argCount, i;
	Word mask, word = 0;

	argCount = String_split(args, ',', &argsArr);

	/*
	WORD binary:
	|31 - opcode - 26|25 - rs - 21|20 - rt - 16|15 - rd - 11|10 - funct - 6|5 - /// - 0| 

	R_1_INS rs, rt, rd 
	*/

	/* writing funct code. */
	mask = ins->functCode;
	word |= (mask << 6);
	/* writing rd. */
	mask = getRegisterNumber(argsArr[2]);
	word |= (mask << 11);
	/* writing rt. */
	mask = getRegisterNumber(argsArr[1]);
	word |= (mask << 16);
	/* writing rs. */
	mask = getRegisterNumber(argsArr[0]);
	word |= (mask << 21);
	/* writing opcode */
	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* Writes a word to the code segment buffer encoding the R_2 instruction call */
static void R_2_encode(void *instructionData, String args) {
	InstructionData *ins = instructionData;
	String *argsArr;
	int argCount, i;
	Word mask, word = 0;

	argCount = String_split(args, ',', &argsArr);

	/* 
	WORD binary:
	|31 - opcode - 26|25 - rs - 21|20 - rt - 16|15 - rd - 11|10 - funct - 6|5 - /// - 0| 

	R_2_INS rd, rs 
	*/

	/* writing funct code. */
	mask = ins->functCode;
	word |= (mask << 6);
	/* writing rd. */
	mask = getRegisterNumber(argsArr[0]);
	word |= (mask << 11);
	/* writing rs. */
	mask = getRegisterNumber(argsArr[1]);
	word |= (mask << 21);
	/* writing opcode */
	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}


/* Writes a word to the code segment buffer encoding the I_1 instruction call */
static void I_1_encode(void *instructionData, String args) {
	InstructionData *ins = instructionData;
	String *argsArr;
	int argCount, i;
	Word mask, word = 0, clear = 0xFFFFFFFF;

	argCount = String_split(args, ',', &argsArr);

	/* 
	WORD binary:
	|31 - opcode - 26|25 - rs - 21|20 - rt - 16|15 - immediate - 0| 

	I_1_INS rs, immediate, rt 
	*/

	/* writing immed. */
	mask = getImmediateNumber(argsArr[1]);
	word |= mask;
	word &= (clear >> 16); /* immed may be a negative number so must clear sign extention */
	/* writing rt. */
	mask = getRegisterNumber(argsArr[2]);
	word |= (mask << 16);
	/* writing rs. */
	mask = getRegisterNumber(argsArr[0]);
	word |= (mask << 21);
	/* writing opcode */
	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* Writes a word to the code segment buffer encoding the I_2 instruction call */
static void I_2_encode(void *instructionData, String args) {
	InstructionData *ins = instructionData;
	String *argsArr;
	int argCount, immediateAddress, i;
	Word mask, word = 0, clear = 0xFFFFFFFF;
	char msg[256];

	Dictionary *labelDict;
	LabelData *labeldata;

	argCount = String_split(args, ',', &argsArr);
	labelDict = AssemblerState_getLabelDictionary();
	labeldata = Dictionary_getValue(labelDict, argsArr[2]);


	/* 
	WORD binary:
	|31 - opcode - 26|25 - rs - 21|20 - rt - 16|15 - immediate - 0| 

	I_2_INS rs, rt, (LABEL / immediate )* ** :

	*	immediate is the relative address of the label [label address - current address]
		- warn if tag references data segment
	**	LABEL address must be defined in this file, .external TAG is illegal.

	*/




	/* absolute address is 0 if extern, -1 if undefined */
	if( (!labeldata) || LabelData_getAbsoluteAddress(labeldata) <= 0 ) {
		sprintf(msg,
				 "The label '%s' is not defined locally, and cannot be used.",
				  argsArr[2]);
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
		goto I_2_encode_exit;
	}

	immediateAddress = labeldata->segmentAddress - AssemblerState_getCurrentCodeSegmentAddress();

	/* memeory is from 0 to 2^25 -1, but immed can ony hold 16 bits */
	if(immediateAddress < HALF_L_BOUND || immediateAddress > HALF_U_BOUND) {
		sprintf(msg,
				 "The label '%s' refers to an address too far away for this operation",
				  argsArr[2]);
		el_logAssemblyErrorDefault(msg, FATAL);
		AssemblerState_addFatalError();
		goto I_2_encode_exit;
	}
	
	/* warn if label refers to data segment */
	if(labeldata->type == DATA) {
		sprintf(msg,
				 "The label '%s' refers to the Data Segement. Behaviour undefined",
				  argsArr[2]);
		el_logAssemblyErrorDefault(msg, WARNING);
	}

	/* writing immed. */
	mask = immediateAddress;
	word |= mask;
	word &= (clear >> 16);	/* immed may be a negative number so must clear sign extention */
	/* writing rt. */
	mask = getRegisterNumber(argsArr[1]);
	word |= (mask << 16);
	/* writing rs. */
	mask = getRegisterNumber(argsArr[0]);
	word |= (mask << 21);
	/* writing opcode */
	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);

I_2_encode_exit:

	for(i = 0; i < argCount; i++) {
		free(argsArr[i]);
	}
	free(argsArr);
}

/* Writes a word to the code segment buffer encoding the I_3 instruction call */
static void I_3_encode(void *instructionData, String args) {
	/* function signature and encoding is the same as I_1 type instructions */
	I_1_encode(instructionData, args);
}

/* Writes a word to the code segment buffer encoding the J_1 instruction call */
static void J_1_encode(void *instructionData, String args) {
	InstructionData *ins = instructionData;
	String arg = String_trim(args); /* new string requires free */
	Boolean isRegister;
	int immediateAddress;
	Word mask, word = 0;
	char msg[256];


	isRegister = isValidRegister(arg);
	if(isRegister) {
		immediateAddress = getRegisterNumber(arg);
	} 
	else {
		
		Dictionary *labelDict = AssemblerState_getLabelDictionary();
		LabelData *labeldata = Dictionary_getValue(labelDict, arg);

		immediateAddress = LabelData_getAbsoluteAddress(labeldata);

		/* if label is not defined locally and label is not extern, absolute address = -1 */
		if( immediateAddress < 0 ) {
			sprintf(msg,
					 "The label '%s' is not defined locally, and is not external.",
					  arg);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
			goto J_1_encode_exit;
		}

		/* warn if label refers to data segment - special no warning for la */
		if(labeldata->type == DATA && ins->opCode != 31) {
			sprintf(msg,
					 "The label '%s' refers to the Data Segement. Behaviour undefined",
					  arg);
			el_logAssemblyErrorDefault(msg, WARNING);
		}
		
		if(labeldata->scope == EXTERNAL) {
			AssemblerState_writeLabelToExternFileBuffer(arg);
		}	
	}
	
	/*
		WORD binary:
		|31 - opcode - 26|25 - reg* - 25|24 - address - 0| 

		*reg is a single bit:	0 <=> address is tag to be evaluated at compile time.
								1 <=> address arg is a $register. 

		J_1_INS* address / $address :
		* (consider warning for data segment address as jmp arg)
	*/

	/* writing immed. */
	mask = immediateAddress;
	word |= mask;
	/* writing reg. */
	mask = isRegister;
	word |= (mask << 25);
	/* writing opcode */
	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);

J_1_encode_exit:
	free(arg);
}

/* Writes a word to the code segment buffer encoding the J_2 instruction call */
static void J_2_encode(void *instructionData, String args) {
	/* J_2 type instyructions are encoded exatly like J_1. */
	J_1_encode(instructionData, args);
}
/* Writes a word to the code segment buffer encoding the J_3 instruction call */
static void J_3_encode(void *instructionData, String args) {
	/* stop instruction only */
	InstructionData *ins = instructionData;
	Word mask, word = 0;

	mask = ins->opCode;
	word |= (mask << 26);

	writeWordToCodeSegmentBufferLittleEndian(word);
}



/* --- FUNCTION DEFINITIONS ------------------------------ */

/* creates a new instruction data instance */
void *InstructionData_init() {
	InstructionData *ins = malloc(sizeof(*ins));

	ins->type = R;
	ins->opCode = 0;
	ins->functCode = 0;
	ins->validateArgs = NULL;
	ins->encode = NULL;

	return ins;
}
/* frees an instruction data instance */
void InstructionData_free(void *instructionData) {
	free(instructionData);
}

/* creates and populates the instruction dictionary for the assembler state */
void *Instruction_getInstructionDictionary() {
	String line;
	FILE *filePtr;
	Dictionary *instructionDict;
	int count, i, subtype, temp;
	String *dataArr;

	filePtr = fopen(INSTRUCTIONS_CSV_FILENAME, "r"); /* read only */

	if (filePtr == NULL) {
		char msg[256];
		sprintf(msg, "The file '%s' could not be openned or doesnt exist", INSTRUCTIONS_CSV_FILENAME);
		el_logSystemError(msg, FATAL);
		AssemblerState_addFatalError();
		return NULL;
	}

	instructionDict = Dictionary_init(32);

	while( (line = fm_readLine(filePtr)) ) {
		if(line[0] != '#') {

			InstructionData *ins = InstructionData_init();
			count = String_split(line,',', &dataArr);
			String_tryParseInt(dataArr[4] , &subtype);
			switch (*(dataArr[1])) {
				case 'R':
					ins->type = R;
					switch(subtype) {
						case R_1:
							ins->validateArgs = R_1_validateArgs;
							ins->encode = R_1_encode;
							break;
						case R_2:
							ins->validateArgs = R_2_validateArgs;
							ins->encode = R_2_encode;
							break;
					}

					break;
				case 'I':
					ins->type = I;
					switch(subtype) {
						case I_1:
							ins->validateArgs = I_1_validateArgs;
							ins->encode = I_1_encode;
							break;
						case I_2:
							ins->validateArgs = I_2_validateArgs;
							ins->encode = I_2_encode;
							break;
						case I_3:
							ins->validateArgs = I_3_validateArgs;
							ins->encode = I_3_encode;
							break;
					}

					break;
				case 'J':
					ins->type = J;
					switch(subtype) {
						case J_1:
							ins->validateArgs = J_1_validateArgs;
							ins->encode = J_1_encode;
							break;
						case J_2:
							ins->validateArgs = J_2_validateArgs;
							ins->encode = J_2_encode;
							break;
						case J_3:
							ins->validateArgs = J_3_validateArgs;
							ins->encode = J_3_encode;
							break;
					}
					break;
				
			}

			/* opcode */
			String_tryParseInt(dataArr[2], &temp);
			ins->opCode = temp;
			/* funct */
			String_tryParseInt(dataArr[3], &temp);
			ins->functCode = temp;

			Dictionary_setValue(instructionDict, dataArr[0], ins);

			for(i = 0; i < count; i++) {
				free(dataArr[i]);
			}
			free(dataArr);
		}
	}

	fclose(filePtr);
	return instructionDict;
}

