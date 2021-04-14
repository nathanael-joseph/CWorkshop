/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 13/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "myText.h"

/* --- PRIVATE FUNCTION DECLARATIONS -------------------------------- */

/* prints greeting and input instructions to stdout */
static void printStartMessage();
/* prints contextualised error message to stdout */
static void printErrorMessage(DataStructureType dsType, long unsigned int bytesStored);
/* 
reads text from stdin and writes it to the data structure.
returns -1 if a malloc error occurs, 0 otherwise. 
*/
static int readText(DataStructure *ds, long unsigned int *bytesStored);
/* reads text from the data structure and prints it to stdout */
static void writeText(DataStructure *ds);
/* gets user input for selected data structure */
static DataStructureType getInputDataStructure(void);

/* --- MAIN --------------------------------------------------------- */
int main(void) {

	long unsigned int bytesStored;
	int hasError;
	DataStructureType dsType; /* enum value to store the type */
	DataStructure *ds; /* pointer to data structure */

	printStartMessage();

	dsType = getInputDataStructure();

	ds = buildDataStructure(dsType);

	hasError = readText(ds, &bytesStored);
	
	if(hasError) {
		printErrorMessage(ds->type, bytesStored);
	} else {
		writeText(ds);	
		printf("\n-----------------------------------------------\n");
		printf("TOTAL bytes stored: %lu \n", bytesStored);
	}
	

	return hasError;

}

/* --- PRIVATE FUNCTION DEFINITIONS -------------------------------- */

/* prints greeting and input instructions to stdout */
static void printStartMessage() {
	printf("\nPlease choose a datastructure. The data strucutures available are: \n");
	printf(" %d - %s - Grows exponencially (2^n) initial size: 256 bytes.\n", 
		dynamicBuffer,
		getDataStructureDisplayName(dynamicBuffer));
	printf(" %d - %s - Grows liniarly (n) initial size: 256 bytes.\n", 
		linkedList,
		getDataStructureDisplayName(linkedList));	
}

/* prints contextualised error message to stdout */
static void printErrorMessage(DataStructureType dsType, long unsigned int bytesStored) {
	
	char *dsName = getDataStructureDisplayName(dsType);
	
	printf("Memory Allocation Error for: %s.\n",dsName);
	printf("Bytes successfully stored: %lu.\n", bytesStored);	

}

/* 
reads text from stdin and writes it to the data structure.
returns -1 if a malloc error occurs, 0 otherwise. 
*/
static int readText(DataStructure *ds, long unsigned int *bytesStored) {

	char c;
	int hasError = 0;
	*bytesStored = 0;
	
	while ((c = getchar()) != EOF) {
		if (c != NEW_LINE) {
			 hasError = ds->writeChar(ds->this, c);
			 if (hasError) {
			 	return -1;
			 }
			 (*bytesStored)++;
		}
	}

	return 0;
}

/* reads text from the data structure and prints it to stdout */
static void writeText(DataStructure *ds) {
	
	char c;
	long unsigned int counter = 0;

	printf("\n\n");
	
	while((c = ds->readChar(ds->this)) != EOF) {
		putchar(c);
		counter++;
		if (counter % MAX_LINE_LENGTH == 0) {
			putchar(NEW_LINE);
		}
	}

}

/* gets user input for selected data structure */
static DataStructureType getInputDataStructure(void) {

	int dsType;
	int scannedSuccessfully;

	scannedSuccessfully = scanf("%d", &dsType);
	while(scannedSuccessfully < 1 || dsType < DSTYPE_LBOUND || dsType > DSTYPE_UBOUND ) {	
		while(getchar() != '\n');
		printf("Could not parse a valid option.\n");
		printf("Please enter either %d or %d: \n >", dynamicBuffer, linkedList);
		scannedSuccessfully = scanf("%d", &dsType);
	}
	printf("\n");
	return dsType;
}