/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 10/04/2021
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
static void printErrorMessage(dataStructure dsType, long unsigned int);
/* reads text from the data structure and prints it to stdout */
static void printFromDataStructure(
			char (*dataStructureReadChar)(void *), /* pointer to dsReadChar function */
			void *ds);
/* gets user input for selected data structure */
static dataStructure getInputDataStructure(void);

/* --- MAIN --------------------------------------------------------- */
int main(void) {

	char c;
	long unsigned int bytesCounter = 0;
	int hasError = 0;
	dataStructure dsType; /* enum value to store the type */
	void *ds; /* pointer to data structure */

	/* function pointers for read, write, and init */
	void *(*dataStructureInit)();
	int (*dataStructureWriteChar)(void *, char);
	char (*dataStructureReadChar)(void *);
	

	printStartMessage();

	dsType = getInputDataStructure();

	/* set function pointers based on selection */
	switch(dsType)
	{
		case dynamicBuffer:
			dataStructureInit = dynamicBufferInit;
			dataStructureWriteChar = dynamicBufferWriteChar;
			dataStructureReadChar = dynamicBufferReadChar;
			break;
		case linkedList:
			dataStructureInit = linkedListInit;
			dataStructureWriteChar = linkedListWriteChar;
			dataStructureReadChar = linkedListReadChar;
			break;
	}

	/* instantiate the chosen data structure */
	ds = (*dataStructureInit)();

	/* read from stdin and write to data structure */
	while ((c = getchar()) != EOF) {
		if (c != NEW_LINE) {
			 hasError = (*dataStructureWriteChar)(ds, c);
			 if (hasError) {
			 	printErrorMessage(dsType, bytesCounter);
			 	return -1;
			 }
			 bytesCounter++;
		}
	}
	
	printFromDataStructure(dataStructureReadChar, ds);

	return 0;

}

/* --- PRIVATE FUNCTION DEFINITIONS -------------------------------- */

/* prints greeting and input instructions to stdout */
static void printStartMessage() {
	printf("Please choose a datastructure. The data strucutures available are: \n");
	printf(" %d - Dynamic Buffer - Grows exponencially (2^n) initial size: 256 bytes.\n", dynamicBuffer);
	printf(" %d - Linked List - Grows liniarly (n) initial size: 256 bytes.\n", linkedList);	
}

/* prints contextualised error message to stdout */
static void printErrorMessage(dataStructure dsType, long unsigned int bytesStored) {
	char *dsName;
	
	switch (dsType)
	{
		case dynamicBuffer: dsName = "Dynamic Buffer"; break;
		case linkedList: dsName = "Linked List"; break;
	}

	printf("Memory Allocation Error for: %s.\n",dsName);
	printf("Bytes successfully stored: %lu.\n", bytesStored);
}

/* reads text from the data structure and prints it to stdout */
static void printFromDataStructure(
			char (*dataStructureReadChar)(void *), /* pointer to dsReadChar function */
			void *ds)
{
	char c;
	long unsigned int counter = 0;

	while((c = (*dataStructureReadChar)(ds)) != EOF) {
		putchar(c);
		counter++;
		if (counter % MAX_LINE_LENGTH == 0) {
			putchar(NEW_LINE);
		}
	}

}

/* gets user input for selected data structure */
static dataStructure getInputDataStructure(void) {

	int dsType;
	int scannedSuccessfully;

	scannedSuccessfully = scanf("%d", &dsType);
	while(scannedSuccessfully < 1 || dsType < dynamicBuffer || dsType > linkedList ) {	
		while(getchar() != '\n');
		printf("Could not parse a valid option.\n");
		printf("Please enter either %d or %d: \n >", dynamicBuffer, linkedList);
		scannedSuccessfully = scanf("%d", &dsType);
	}

	return dsType;
}