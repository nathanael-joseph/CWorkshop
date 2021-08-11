/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 07/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "assembler.h"

/* --- STATIC FUNCTION DECLARATIONS --------------------------------- */

/* Prints an error message and exits the program if no arguments were provided */ 
static void validateArgc(int argc);
/* Validates a line from the .asm file, and populates the labels dictionary - first pass */
static void singleLineFirstPass(String line);
/* writes code or data bytes to file buffers and does additional validfations - second pass*/
static void singleLineSecondPass(String line);
/* performs first pass for entire file */
static void runFirstPass();
/* performs second pass for entire file */
static void runSecondPass();
/* 
	a callback function for the label dictionary's foreach method 
	that will write the each entry label to the state's entry buffer.
*/
static void writeEntryLabelsCallback(String labelname, void *labeldata, void *args);
/* writes to the entry file buffer and then to entry file if there are entries*/
static void writeEntryFile();
/* writes the extern file buffer's content to the .ext file if it is not empty */
static void writeExternFile();
/* writes the object file if the there is content to write */
static void writeObjectFile();
/* writes the output files */
static void writeOutputFiles();

/* --- MAIN --------------------------------------------------------- */

int main (int argc, char **argv) {
	int i, j;

	/* array of void function() pointers */
	Action pipeline[PIPELINE_ACTION_COUNT] = {
		runFirstPass,
		AssemblerState_finalizeFirstPass,
		runSecondPass,
		writeOutputFiles
	};

	validateArgc(argc); 
	AssemblerState_init(); 

	i = 1;
	AssemblerState_set(*(argv + i)); 

	for(j = 0; j < PIPELINE_ACTION_COUNT &&  !AssemblerState_hasFatalError(); j++) {
		pipeline[j]();
	}
	
	while(++i < argc) {

		AssemblerState_reset(*(argv + i)); 

		for(j = 0; j < PIPELINE_ACTION_COUNT &&  !AssemblerState_hasFatalError(); j++) {
			pipeline[j]();
		}

	}
	

	AssemblerState_free(); 
	return 0;
}

/* --- STATIC FUNCTION DEFINITIONS ---------------------------------- */

/* Prints an error message and exits the program if no arguments were provided */ 
static void validateArgc(int argc) {
	if (argc < 2) {
		el_logSystemError("No filename arguments were provided", FATAL); 
		el_logSystemError("Try executing: ./assembler myasmfile.asm anotherasmfile.asm ", INFO);
		exit(-1);
	}
}

/* Validates a line from the .asm file, and populates the labels dictionary - first pass */
static void singleLineFirstPass(String line) {
	Boolean isDirective = false;
	int commandLength;
	char *colonPtr;
	char labelBfr[256], commandBfr[256], msg[256]; 

	String trimmedLine; /* pointer to beginning of line after whitespaces */
	String commandLine; /* pointer to the beginning of the line after the label if there is one */

	Dictionary *labelDict;
	Dictionary *instructionDict;
	Dictionary *directiveDict; 

	LabelData *labelData;
	InstructionData *instructionData = NULL;
	DirectiveData *directiveData = NULL;

	trimmedLine = line;
	while(char_isWhitespace(*trimmedLine)) {
		trimmedLine++;
	}
	
	/*len = strlen(trimmedLine); */

	/* check if line is a comment or is empty */
	if(strlen(trimmedLine) == 0 || trimmedLine[0] == COMMENT_CHAR) {
		return;
	}

	commandLine = trimmedLine;

	/* if line has label */
	if((colonPtr = strchr(trimmedLine, ':')) ) {
		commandLine = colonPtr + 1;
		while(char_isWhitespace(*commandLine)) {
			commandLine++;
		}
	}

	/* proccess instruction / directive line */
	if(commandLine[0] == '.') {
		isDirective = true;
		commandLine++;
	}

	/* increment commandLength to end of word (first whitespace char or EOF ) */
	for(commandLength = 0; 
		!char_isWhitespace(commandLine[commandLength]) && commandLine[commandLength] != EOF;
		commandLength++);

	strncpy(commandBfr, commandLine, commandLength);
	commandBfr[commandLength] = '\0';


	if(! isDirective) {
		instructionDict = AssemblerState_getInstructionDisctionary();

		instructionData = Dictionary_getValue(instructionDict, commandBfr);
		/* if not valid instruction */
		if(! instructionData) {
			sprintf(msg, "'%s' is not a valid instruction.", commandBfr);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
		}

	} 
	else {
		directiveDict = AssemblerState_getDirectiveDisctionary();

		directiveData = Dictionary_getValue(directiveDict, commandBfr);
		/* if not valid directive */
		if(! directiveData) {
			sprintf(msg, "'.%s' is not a valid directive.", commandBfr);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
		}
	}


	/* if line has label */
	if( colonPtr ) {

		labelDict = AssemblerState_getLabelDictionary();

		/* set label bfr to contain label name */
		strncpy(labelBfr, trimmedLine, colonPtr - trimmedLine);
		labelBfr[colonPtr - trimmedLine] = '\0'; 

		if (! Label_isValidLabelName(labelBfr)) {
			sprintf(msg, "'%s' is not a valid label name.", labelBfr);
			el_logAssemblyErrorDefault(msg, FATAL);
			AssemblerState_addFatalError();
		} 
		else {
			labelData = Dictionary_getValue(labelDict, labelBfr);
			if(!labelData) {
				/* label has not yet been registered in label dictionary, add it */
				labelData = LabelData_init();
				Dictionary_setValue(labelDict, labelBfr, labelData);
			}

			/* check label has not already been defined */
			if(LabelData_hasBeenDefinedLocally(labelData)) {
				sprintf(msg, "The label '%s' has already been defined, or is external ", labelBfr);
				el_logAssemblyErrorDefault(msg, FATAL);
				AssemblerState_addFatalError();
			}
			else {
				/* update label address and type */
				if(isDirective && directiveData) {
					if(directiveData->type == D) {
						labelData->type = DATA;
						labelData->segmentAddress = AssemblerState_getCurrentDataSegmentAddress();
					}
					else {
						sprintf(msg, "cannot place label '%s' on attribute directive", labelBfr);
						el_logAssemblyErrorDefault(msg, FATAL);
						AssemblerState_addFatalError();
					}
				}
				else {
					/* command is instruction */
					labelData->type = CODE;
					/* code segment address is next address, so - 4 */
					labelData->segmentAddress =	AssemblerState_getCurrentCodeSegmentAddress();
				}
			}
		}

	}	/* end label handling */

	/* if instruction or directive exists - call first poass function */ 
	if(isDirective && directiveData) {
		/* invoke validate args funct for this directive, pass arguments string  */
		(*(directiveData->validateArgsAndApply))(commandLine + commandLength);	
	} else if( instructionData ) {
		/* invoke validate args funct for this instruction, pass arguments string  */
		(*(instructionData->validateArgs))(commandLine + commandLength);
		AssemblerState_incrementCurrentCodeSegmentAddress();
	}

}

/* performs first pass for entire file */
static void runFirstPass() {
	FILE *filePtr = AssemblerState_getFile();
	String line;

	while( (line = fm_readLine(filePtr)) ) {
		AssemblerState_incrementLineNumber();
		singleLineFirstPass(line);	
	}
}

/* writes code bytes to code segment file buffer and does additional validfations - second pass*/
static void singleLineSecondPass(String line) {
	Boolean isDirective = false;
	int commandLength;
	char *colonPtr;
	char commandBfr[256];

	String trimmedLine; /* pointer to beginning of line after whitespaces */
	String commandLine; /* pointer to the beginning of the line after the label if there is one */


	Dictionary *instructionDict;
	InstructionData *instructionData;

	trimmedLine = line;
	while(char_isWhitespace(*trimmedLine)) {
		trimmedLine++;
	}
	

	/* check if line is a comment or is empty */
	if( strlen(trimmedLine) == 0 || trimmedLine[0] == COMMENT_CHAR) {
		return;
	}

	commandLine = trimmedLine;

	/* if line has label */
	if((colonPtr = strchr(trimmedLine, ':')) ) {
		commandLine = colonPtr + 1;
		while(char_isWhitespace(*commandLine)) {
			commandLine++;
		}
	}

	/* proccess instruction / directive line */
	if(commandLine[0] == '.') {
		isDirective = true;
		commandLine++;
	}

	/* increment commandLength to end of word (first whitespace char or EOF ) */
	for(commandLength = 0;
		!char_isWhitespace(commandLine[commandLength]) && commandLine[commandLength] != EOF; 
		commandLength++);

	strncpy(commandBfr, commandLine, commandLength);
	commandBfr[commandLength] = '\0';

	if(! isDirective) {
		instructionDict = AssemblerState_getInstructionDisctionary();

		instructionData = Dictionary_getValue(instructionDict, commandBfr);
		/* invoke validate args funct for this instruction, pass arguments string  */
		(*(instructionData->encode))(instructionData, commandLine + commandLength);
		/* writing encoded bytes to the code segment buffer 
		   increments current code segment address address */
	} 
}

/* performs second pass for entire file */
static void runSecondPass() { 
	FILE *filePtr = AssemblerState_getFile();
	String line;

	while( (line = fm_readLine(filePtr)) ) {
		AssemblerState_incrementLineNumber();
		singleLineSecondPass(line);
	}
}

/* 
	a callback function for the label dictionary's foreach method 
	that will write each entry label to the state's entry buffer.
*/
static void writeEntryLabelsCallback(String labelname, void *labeldata, void *args) {
	LabelData *lbd = labeldata;
	if(lbd->scope == ENTRY) {
		AssemblerState_writeLabelToEntryFileBuffer(	labelname,
													LabelData_getAbsoluteAddress(lbd)	
													);
	}
}

/* writes to the entry file buffer and then to entry file if there are entries*/
static void writeEntryFile() {
	char entryFileName[256];
	String asmFileName;
	int len, tempByte;
	FILE *entryFile;
	LinkedListBuffer *entryFileLinkedListBuffer;

	Dictionary_foreach( AssemblerState_getLabelDictionary(),
						writeEntryLabelsCallback,
						NULL	/* args not used */
						);

	entryFileLinkedListBuffer = AssemblerState_getEntryFileBuffer();

	if(! LinkedListBuffer_isEmpty(entryFileLinkedListBuffer)) {

		asmFileName = AssemblerState_getFileName();
		len = strlen(asmFileName);
		strncpy(entryFileName, asmFileName, len -2);
		entryFileName[len-2] = '\0';
		strcat(entryFileName, "ent");

		/* create or override entry file */
		entryFile = fm_createFile(entryFileName); 
		if(entryFile) {
			
			while((tempByte = LinkedListBuffer_readByte(entryFileLinkedListBuffer)) != EOF ) {
				fm_tryWriteByte(entryFile, tempByte);
			}

			fclose(entryFile);
		}

		
	}

}

/* writes the extern file buffer's content to the .ext file if it is not empty */
static void writeExternFile() {
	char externFileName[256];
	String asmFileName;
	int len, tempByte;
	FILE *externFile;
	LinkedListBuffer *externFileLinkedListBuffer;

	externFileLinkedListBuffer = AssemblerState_getExternFileBuffer();

	if(! LinkedListBuffer_isEmpty(externFileLinkedListBuffer)) {

		asmFileName = AssemblerState_getFileName();
		len = strlen(asmFileName);
		strncpy(externFileName, asmFileName, len -2);
		externFileName[len-2] = '\0';
		strcat(externFileName, "ext");

		/* create or override extern file */
		externFile = fm_createFile(externFileName); 
		
		if(externFile) {		
			while((tempByte = LinkedListBuffer_readByte(externFileLinkedListBuffer)) != EOF ) {
				fm_tryWriteByte(externFile, tempByte);
			}
			fclose(externFile);
		}	

	}
}
/* writes the object file if the there is content to write */
static void writeObjectFile() {
	char strBfr[256];
	String asmFileName;
	int len, tempByte;
	FILE *objectFile;
	LinkedListBuffer *codeSegmentLinkedListBuffer;
	LinkedListBuffer *dataSegmentLinkedListBuffer;
	uint32_t addressCounter = CODESEGMENT_START_ADDRESS;

	/* set strBfr to filename.ob */
	asmFileName = AssemblerState_getFileName();
	len = strlen(asmFileName);
	strncpy(strBfr, asmFileName, len -2);
	strBfr[len-2] = '\0';
	strcat(strBfr, "ob");

	/* create or override ob file */
	objectFile = fm_createFile(strBfr); 
	
	if(objectFile) {		

		codeSegmentLinkedListBuffer = AssemblerState_getCodeSegmentBuffer();
		dataSegmentLinkedListBuffer = AssemblerState_getDataSegmentBuffer();
		
		/* print segment sizes */
		fprintf(objectFile,
				"     %d %d ", 
				AssemblerState_getCodeSegmentSize(),
				AssemblerState_getDataSegmentSize()
				);
		
		/* print code segment */
		while((tempByte = LinkedListBuffer_readByte(codeSegmentLinkedListBuffer)) != EOF ) {
			
			if((addressCounter - CODESEGMENT_START_ADDRESS) % 4 == 0 ) {
				fprintf(objectFile, "\n%04u", addressCounter);
			}
			
			fprintf(objectFile, " %02X", tempByte);
			addressCounter++;
		}

		/* print data segment */
		while((tempByte = LinkedListBuffer_readByte(dataSegmentLinkedListBuffer)) != EOF ) {
			
			if((addressCounter - CODESEGMENT_START_ADDRESS) % 4 == 0 ) {
				fprintf(objectFile, "\n%04u", addressCounter);
			}
			
			fprintf(objectFile, " %02X", tempByte);
			addressCounter++;
		}

		fclose(objectFile);
	}	

}

/* writes the output files */
static void writeOutputFiles() {

	writeEntryFile();
	writeExternFile();
	writeObjectFile();

}

