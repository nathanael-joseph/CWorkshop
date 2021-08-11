/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 07/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "assembler_state.h"

/* --- PRIVATE TYPE DEFINITIONS --------------------------- */

typedef struct {
	/* current file */
	String filename;
	FILE *file;
	/* general state variables for calculations during first and second pass */
	uint32_t lineNumber;
	uint32_t codeSegment_currentAddress;
	uint32_t dataSegment_currentAddress;
	uint32_t codeSegment_size;
	uint32_t dataSegment_size;
	/* temp file buffers */
	void *codeSegment_linkedListBuffer; 
	void *dataSegment_linkedListBuffer;
	void *entry_linkedListBuffer;
	void *extern_linkedListBuffer;
	/* hash tables for labels, instructions, and directives */
	void *labelDictionary;
	void *instructionDictionary;
	void *directiveDictionary;
	/* flag to notify whether or not to proceed to second pass or file writing */
	Boolean hasFatalError;
} AssemblerState;

/* --- STATIC VARIABLES ---------------------------------- */

static AssemblerState *_state;

/* --- STATIC FUNCTION DEFINITIONS ----------------------- */

static void AssemblerState_clearProperties() {
	_state->lineNumber = 0;
	_state->codeSegment_currentAddress = 0;
	_state->dataSegment_currentAddress = 0;
	_state->codeSegment_size = 0;
	_state->dataSegment_size = 0;
	_state->hasFatalError = false;
}

/* free's the linkedlist file buffers. */
static void AssemblerState_freeFileBuffers() {
	if(_state->codeSegment_linkedListBuffer ) {
		LinkedListBuffer_free(_state->codeSegment_linkedListBuffer);
		_state->codeSegment_linkedListBuffer = NULL;
	}
	if(_state->dataSegment_linkedListBuffer ) {
		LinkedListBuffer_free(_state->dataSegment_linkedListBuffer);
		_state->dataSegment_linkedListBuffer = NULL;
	}
	if(_state->entry_linkedListBuffer ) {
		LinkedListBuffer_free(_state->entry_linkedListBuffer);
		_state->entry_linkedListBuffer = NULL;
	}
	if(_state->extern_linkedListBuffer ) {
		LinkedListBuffer_free(_state->extern_linkedListBuffer);
		_state->extern_linkedListBuffer = NULL;
	}
}

/* --- FUNCTION DEFINITIONS ------------------------------ */

/* Initiates the Assembler's state and populates the instruction dictionary */
void AssemblerState_init() {
	_state = malloc(sizeof(*_state));

	_state->instructionDictionary = Instruction_getInstructionDictionary();
	_state->directiveDictionary = Directive_getDirectiveDictionary();

	_state->file = NULL;
	_state->labelDictionary = NULL;
	_state->codeSegment_linkedListBuffer = NULL;
	_state->dataSegment_linkedListBuffer = NULL;
	_state->entry_linkedListBuffer = NULL;
	_state->extern_linkedListBuffer = NULL;
}

/* Sets up the state for the first file */
void AssemblerState_set(String filename) {
	char msg[256];

	AssemblerState_clearProperties();

	_state->filename = String_trim(filename); 

	if(! fm_isValidAssemblyFileName(_state->filename)) {
		_state->hasFatalError = true;

		sprintf(msg,
			 	"The file %s does not have the required '.as' file extension ",
			 	filename);
		el_logSystemError(msg, FATAL);

		return;
	}

	_state->file = fopen(_state->filename, "r");

	if(_state->file == NULL) {
		_state->hasFatalError = true;
		el_logAssemblyError("File does not exist or could not be opened. ",
							FATAL,
							_state->filename, 
							_state->lineNumber
							);
		return;
	}

	_state->labelDictionary = Dictionary_init(LABEL_DICTIONARY_INIT_SIZE);
	AssemblerState_initFileBuffers();
}

/* Resets the state for a new file */
void AssemblerState_reset(String filename) {
	char msg[256];

	if(_state->labelDictionary) {
		Dictionary_freeWithCallback(_state->labelDictionary, LabelData_free);
		_state->labelDictionary = NULL;
	}
	/* free file buffers */
	AssemblerState_freeFileBuffers();

	/* close current file pointer */
	if(_state->file != NULL ) {
		if((fclose(_state->file)) == EOF) {
			_state->hasFatalError = true;
			el_logAssemblyError("File could not be closed. ",
								FATAL,
								_state->filename, 
								_state->lineNumber
								);
			return;
		}
	}
	
	_state->file = NULL;

	AssemblerState_clearProperties();

	/* reset the state's filename property */
	free(_state->filename);
	_state->filename = String_trim(filename); 

	/* check valid filename */
	if(! fm_isValidAssemblyFileName(_state->filename)) {
		_state->hasFatalError = true;

		sprintf(msg,
			 	"The file %s does not have the required '.as' file extension ",
			 	filename);
		el_logSystemError(msg, FATAL);

		return;
	}

	/* reset file pointer to new file */
	_state->file = fopen(_state->filename, "r");

	if(_state->file == NULL) {
		_state->hasFatalError = true;
		el_logAssemblyError("File does not exist or could not be opened. ",
							FATAL,
							_state->filename, 
							_state->lineNumber
							);
		return;
	}

	_state->labelDictionary = Dictionary_init(LABEL_DICTIONARY_INIT_SIZE);
	AssemblerState_initFileBuffers();
}

/* Initiates the linkedlist file buffers. */
void AssemblerState_initFileBuffers() {
	_state->codeSegment_linkedListBuffer = LinkedListBuffer_init();
	_state->dataSegment_linkedListBuffer = LinkedListBuffer_init();
	_state->entry_linkedListBuffer = LinkedListBuffer_init();
	_state->extern_linkedListBuffer = LinkedListBuffer_init();
}

/* Frees the Assembler's state */
void AssemblerState_free() {
	/* close current file pointer */
	if(_state->file != NULL ) {
		if((fclose(_state->file)) == EOF) {
			_state->hasFatalError = true;
			el_logAssemblyError("File could not be closed. ",
								FATAL,
								_state->filename, 
								_state->lineNumber
								);
			return;
		}
	}

	free(_state->filename);

	if(_state->labelDictionary) {
		Dictionary_freeWithCallback(_state->labelDictionary, LabelData_free);
	}

	Dictionary_freeWithCallback(_state->instructionDictionary, InstructionData_free); 
	Dictionary_freeWithCallback(_state->directiveDictionary, DirectiveData_free);

	/* free file buffers */
	AssemblerState_freeFileBuffers();

	free(_state);	
}

/* resets file pointer to beginning of file, calculates segment sizes, etc. */
void AssemblerState_finalizeFirstPass() {
	uint32_t totalSize;

	_state->codeSegment_size = _state->codeSegment_currentAddress;
	_state->dataSegment_size = _state->dataSegment_currentAddress;

	_state->lineNumber = 0;
	_state->codeSegment_currentAddress = 0;

	rewind(_state->file);

	totalSize = CODESEGMENT_START_ADDRESS
				+ _state->codeSegment_size 
				+ _state->dataSegment_size;
				
	if(totalSize > MEMORY_SIZE) {
		el_logAssemblyErrorDefault("Memory size exceeded", FATAL);
		AssemblerState_addFatalError();
	}
}

/* Returns pointer to the current label dictionary */
void *AssemblerState_getLabelDictionary() {
	return _state->labelDictionary;
}
/* Returns pointer to the instruction dictionary */
void *AssemblerState_getInstructionDisctionary() {
	return _state->instructionDictionary;
}
/* Returns pointer to the directive dictionary */
void *AssemblerState_getDirectiveDisctionary() {
	return _state->directiveDictionary;
}
/* Increments the current line numberin the state, and returns the new value */ 
uint32_t AssemblerState_incrementLineNumber() {
	return ++(_state->lineNumber);
}
/* Returns the current line number in the state */ 
uint32_t AssemblerState_getLineNumber() {
	return _state->lineNumber;
}
/* returns the current code segment address */
uint32_t AssemblerState_getCurrentCodeSegmentAddress() {
	return _state->codeSegment_currentAddress;
}
/* returns the current data segment address */
uint32_t AssemblerState_getCurrentDataSegmentAddress() {
	return _state->dataSegment_currentAddress;
}
/* adds 4 to the current code segment address */
void AssemblerState_incrementCurrentCodeSegmentAddress() {
	_state->codeSegment_currentAddress += 4;

	if (_state->codeSegment_currentAddress >= MEMORY_SIZE ) {
		el_logAssemblyErrorDefault("Memory size exceeded", FATAL);
		AssemblerState_addFatalError();
	}
}
/* adds argument amount to current data segment address */
void AssemblerState_incrementCurrentDataSegmentAddress(uint32_t amount) {
	_state->dataSegment_currentAddress += amount;

	if (_state->dataSegment_currentAddress >= MEMORY_SIZE ) {
		el_logAssemblyErrorDefault("Memory size exceeded", FATAL);
		AssemblerState_addFatalError();
	}
}
/* returns the code segment size */
uint32_t AssemblerState_getCodeSegmentSize() {
	return _state->codeSegment_size;
}
/* returns the data segment size */
uint32_t AssemblerState_getDataSegmentSize() {
	return _state->dataSegment_size;
}
/* Returns the name of the current state's file */
String AssemblerState_getFileName() {
	return _state->filename;
}
/* Returns the current state's file pointer */
FILE *AssemblerState_getFile() {
	return _state->file;
}
/* Sets the state's hasFatalError flag to true */
void AssemblerState_addFatalError() {
	_state->hasFatalError = true;
}
/* Returns true if a fatal error has been added to the state, false otherwise */
Boolean AssemblerState_hasFatalError() {
	return _state->hasFatalError;
}
/* writes a byte to the Code segment linked list buffer */
void AssemblerState_writeByteToCodeSegmentBuffer(Byte byte) {
	LinkedListBuffer_writeByte(_state->codeSegment_linkedListBuffer, byte);
	_state->codeSegment_currentAddress++;
}
/* writes a byte to the Data segment linked list buffer */
void AssemblerState_writeByteToDataSegmentBuffer(Byte byte) {
	LinkedListBuffer_writeByte(_state->dataSegment_linkedListBuffer, byte);
	_state->dataSegment_currentAddress++;
}
/* writes a formatted line in the entry file buffer using state properties and argumeent label */
void AssemblerState_writeLabelToEntryFileBuffer(String label, uint32_t absoluteAddress) {
	char line[256];

	sprintf(line, "%s %04u\n",label, absoluteAddress);
	LinkedListBuffer_writeString(_state->entry_linkedListBuffer,
								line);
}
/* writes a formatted line in the extern file buffer using state properties and argumeent label */
void AssemblerState_writeLabelToExternFileBuffer(String label) {
	char line[256];
	uint32_t commandAddress = CODESEGMENT_START_ADDRESS +
							  AssemblerState_getCurrentCodeSegmentAddress();
							  
	sprintf(line, "%s %04u\n",label, commandAddress);
	LinkedListBuffer_writeString(_state->extern_linkedListBuffer,
								line);
}
/* returns the code segment's linked list buffer */
void *AssemblerState_getCodeSegmentBuffer() {
	return _state->codeSegment_linkedListBuffer;
}
/* returns the data segment's linked list buffer */
void *AssemblerState_getDataSegmentBuffer() {
	return _state->dataSegment_linkedListBuffer;
}
/* returns the entry file's linked list buffer */
void *AssemblerState_getEntryFileBuffer() {
	return _state->entry_linkedListBuffer;
}
/* returns the extern file's linked list buffer */
void *AssemblerState_getExternFileBuffer() {
	return _state->extern_linkedListBuffer;
}
