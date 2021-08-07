/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 06/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "label.h"

/* --- FUNCTION DEFINITIONS ------------------------------ */

/* creates a new labeldata instance */
LabelData *LabelData_init() {
	LabelData *labeldata = malloc(sizeof(*labeldata));
	labeldata->segmentAddress = -1;
	labeldata->scope = LOCAL;
	labeldata->type = UNDEFINED;
	
	return labeldata;
}

/* frees a labeldata instance */
void LabelData_free(void *labeldata) {
	free(labeldata);
}

/* 
	Returns the absolute address of a label, or -1 if it has not been defined.
	If the address is external 0 will be returned. 
*/
int32_t LabelData_getAbsoluteAddress(void *labeldata) {
	LabelData *ld = labeldata;
	int32_t address;

	if( ld->segmentAddress == -1 ) {

		if( ld->scope == EXTERNAL ) {
			address = 0;
		}
		else {
			address = ld->segmentAddress;
		}

	} else {

		if(ld->type == DATA) {
			address = CODESEGMENT_START_ADDRESS 
						+ AssemblerState_getCodeSegmentSize() 
						+ ld->segmentAddress;
		}	
		else {
			address = CODESEGMENT_START_ADDRESS 
						+ ld->segmentAddress;
		}
		
	}

	return address;
}

/* 
	returns true if the label's address has allready been defined, 
	or if it has already been marked as external
*/
Boolean LabelData_hasBeenDefinedLocally(void *labeldata) {
	return LabelData_getAbsoluteAddress(labeldata) > -1;
}

/* Returns true if a tag name meets required format, false otherwise. */
Boolean Label_isValidLabelName(String name) {
	int i; 
	Dictionary *instructionDict;
	Dictionary *directiveDict;

	if(strlen(name) <= 31 && (char_isLowerCase(name[0]) || char_isUpperCase(name[0])) ) {
		
		for(i = 0 ; i < strlen(name); i++) {
			if(!char_isLetterOrNumber(name[i])) {
				return false;
			}
		}

		instructionDict = AssemblerState_getInstructionDisctionary();
		if(Dictionary_containsKey(instructionDict, name)) {
			return false;
		}

		directiveDict = AssemblerState_getDirectiveDisctionary();
		if(Dictionary_containsKey(directiveDict, name)) {
			return false;
		}

	} 
	else {
		return false;
	}

	return true;
}
