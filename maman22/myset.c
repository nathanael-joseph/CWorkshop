/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/04/2021
Written for: The Open University Of Israel
Course: 204equals65 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "myset.h"

/* --- PRIVATE FUNCTION DECLARATIONS -------------------------------- */
/* --- MAIN --------------------------------------------------------- */
int main(int argc, char **argv) {

	Boolean stop = false;
	String line;
	
	while((line = readLine())) {
		executeLine(line, &stop);
		if (stop) 
			break;
	}

	return 0;
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* Parses the line of text, and executes the command if possible,
else prints an error massage */
void executeLine(String line, Boolean *stop) {
	
	int firstWhitespaceIndex = 0;
	String functionName;
	String trimmedLine = string_trim(line); /* new string */

	/* find index of first white space char in command line */
	while(	(trimmedLine[firstWhitespaceIndex] != '\0') &&
			(!char_isWhitespace(trimmedLine[firstWhitespaceIndex++])));

	if (firstWhitespaceIndex == 0) {
		/* empty line -> no-op */
		goto finish;
	}

	functionName = calloc(firstWhitespaceIndex, sizeof(*functionName));

	strncpy(functionName, trimmedLine, firstWhitespaceIndex);

	/* this if statement is only to handle the edge case of no
	 whitespace character, like "STOP[EOF]" */
	if(char_isWhitespace(functionName[firstWhitespaceIndex - 1])) {
		functionName[firstWhitespaceIndex - 1] = '\0';		
	}


	if (string_equals(functionName, READ_SET)) {
		executeReadSet(trimmedLine + firstWhitespaceIndex);
	} 
	else if (string_equals(functionName, PRINT_SET)) {
		executePrintSet(trimmedLine + firstWhitespaceIndex);
	} /*
	else if (string_equals(functionName, UNION_SET)) {
		executeUnionSet(trimmedLine + firstWhitespaceIndex);	
	} 
	else if (string_equals(functionName, INTERSECT_SET)) {
		executeIntersectSet(trimmedLine + firstWhitespaceIndex);
	} 
	else if (string_equals(functionName, SUB_SET)) {
		executeSubSet(trimmedLine + firstWhitespaceIndex);
	} 
	else if (string_equals(functionName, SYMDIFF_SET)) {
		executeSymDiffSet(trimmedLine + firstWhitespaceIndex);
	} */
	else if (string_equals(functionName, STOP)) {
		*stop = true;
	} 
	else {
		em_throwInvalidFunctionError(functionName);
	}

	free(functionName);

	finish:
	free(trimmedLine);
	return;
}
/* Parses the function arguments from the String CSV and 
executes read_set if possible, else prints an error message */
void executeReadSet(String argsCSV) {
	
	String *args;
	int i, argCount, temp;
	Set *set, *tempSet;

	argCount = string_split(argsCSV, ',', &args);
	
	/* check there is at least one argument */
	if(argCount < 2) {
		em_throwInvalidArgumentCountError(); 
		goto finish;
	}
	
	/* check first arg is valid set */
	if((set = getSet(args[0])) == NULL) {
		em_throwInvalidArgumentError(args[0]);
		goto finish;
	}


	/* check last arg is terminator (-1) */
	if(string_tryParseInt(args[argCount-1], &temp)) {
		if(temp != -1) {
			em_throwInvalidFunctionTerminationError();
			goto finish;
		}
	} else {
		em_throwInvalidArgumentError(args[argCount-1]);
		goto finish;
	}

	/* check each arg inbetween is in range */
	for(i = 1; i < argCount - 1; i++) {
		if(string_tryParseInt(args[i], &temp)) {
			if(temp < SET_LBOUND || temp > SET_UBOUND) {
				em_throwArgumentOutOfRangeError(args[i]);
				goto finish;
			}
		} else {
			em_throwInvalidArgumentError(args[i]);
			goto finish;
		}
	}

	/* all good */
	tempSet = set_init();
	for(i = 1; i < argCount -1; i++) {
		string_tryParseInt(args[i], &temp);
		set_insert(tempSet, temp - 1); /* set holds (0-127), displays (1-128) */
	}
	set_copy(set, tempSet);

	free(tempSet);
	
	finish:

	/* free args */
	for(i = 0; i < argCount; i++) {
		free(args[i]);
	}
	free(args); 

	return;
}
/* Parses the function arguments from the String CSV and 
executes print_set if possible, else prints an error message */
void executePrintSet(String argsCSV) {
	String *args;
	int argCount, i;
	Set *set;

	argCount = string_split(argsCSV, ',', &args);

	/* check for the right number of arguments */
	if(argCount > 1) {
		em_throwInvalidArgumentCountError();
		goto finish;
	}

	/* check first arg is valid set */
	if((set = getSet(args[0])) == NULL) {
		em_throwInvalidArgumentError(args[0]);
		goto finish;
	}

	printSet(set);

	finish:
	/* free args */
	for(i = 0; i < argCount; i++) {
		free(args[i]);
	}
	free(args); 
	return;
}
/* Parses the function arguments from the String CSV and 
executes union_set if possible, else prints an error message */
void executeUnionSet(String argsCSV);
/* Parses the function arguments from the String CSV and 
executes intersect_set if possible, else prints an error message */
void executeIntersectSet(String argsCSV);
/* Parses the function arguments from the String CSV and 
executes sub_set if possible, else prints an error message */
void executeSubSet(String argsCSV);
/* Parses the function arguments from the String CSV and 
executes symdiff_set if possible, else prints an error message */
void executeSymDiffSet(String argsCSV);




/* returns a pointer to the set with the specified name,
or null if the set name does not exist */
Set *getSet(String name) {
	static Boolean init = false;
	static Set *A, *B, *C, *D, *E, *F;
	if(!init) {
		A = set_init();
		B = set_init();
		C = set_init();
		D = set_init();
		E = set_init();
		F = set_init();
		init = true;
	}
	
	if (string_equals(name, SETA)) {
		return A;
	} else if (string_equals(name, SETB)) {
		return B;
	} else if (string_equals(name, SETC)) {
		return C;
	} else if (string_equals(name, SETD)) {
		return D;
	} else if (string_equals(name, SETE)) {
		return E;
	} else if (string_equals(name, SETF)) {
		return F;
	} else {
		return NULL;
	}

}

/* Returns a pointer to the next line in stdin, without 
the ending '\n' character, or null if there are no more lines
to read. Exits if a line is too long.
Memory safe - no malloc/free required.
*/
String readLine() {

	static char line[MAX_LINE_LENGTH];
	char *newlineCharPtr;

	fgets(line, MAX_LINE_LENGTH,stdin);

	/* remove the new line '\n' char is there is one */
	if((newlineCharPtr = strchr(line,'\n')) != NULL) {
		*newlineCharPtr = '\0';
	}

	return line;
}

/* prints the contents of the set to stdin, or "set is empty" */
void printSet(void *set) {
	Set *s = set;
	int i;
	if (set_isEmpty(s)) {
		printf("Emmpty set\n");
	} else {
		printf("{");
		for(i = 0; i < SET_UBOUND; i++) {
			if(set_contains(s, i)) {
				printf("[%d]",i+1);
			}
		}
		printf("}\n");
	}
}