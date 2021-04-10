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

int main(void) {
	int i,j;
	char c;
	char * mystring = "this is a longer string than usuall \n";


	void *(*dataStructureInit)();
	int (*dataStructureWriteChar)(void *, char);
	char (*dataStructureReadChar)(void *);
	void *dataStructure;


	printf("Testing Buffer DS \n==================== \n");
	/* test buffer */
	dataStructureInit = bufferInit;
	dataStructureWriteChar = bufferWriteChar;
	dataStructureReadChar = bufferReadChar;
	dataStructure = (*dataStructureInit)();

	for(j= 0; j< 500; j++) {
		for(i = 0; mystring[i] != 0; i++) {
			(*dataStructureWriteChar)(dataStructure, mystring[i]);
		}
	}
	
	while((c = (*dataStructureReadChar)(dataStructure)) != EOF) {
		putchar(c);
	}

	printf("Testing Buffer DS \n==================== \n");
	/* test buffer */
	dataStructureInit = linkedListInit;
	dataStructureWriteChar = linkedListWriteChar;
	dataStructureReadChar = linkedListReadChar;
	dataStructure = (*dataStructureInit)();

	for(j= 0; j< 500; j++) {
		for(i = 0; mystring[i] != 0; i++) {
			(*dataStructureWriteChar)(dataStructure, mystring[i]);
		}
	}
	
	while((c = (*dataStructureReadChar)(dataStructure)) != EOF) {
		putchar(c);
	}

	return 0;

}