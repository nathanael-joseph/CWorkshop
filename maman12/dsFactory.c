/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 13/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#include "dsFactory.h"

/* --- FUNCTION DEFINITIONS ------------------------------ */

/* 
return a pointer to an instanciated DataStructure of type argument 'type',
or NULL if a memory allocation error occured.
*/
void *buildDataStructure(DataStructureType type) {

	DataStructure *ds = malloc(sizeof(*ds));

	if(ds == NULL) {
		return NULL;  /* malloc failed */
	}

	switch(type)
	{
		case dynamicBuffer:
			ds->init = dynamicBufferInit;
			ds->writeChar = dynamicBufferWriteChar;
			ds->readChar = dynamicBufferReadChar;
			break;
		case linkedList:
			ds->init = linkedListInit;
			ds->writeChar = linkedListWriteChar;
			ds->readChar = linkedListReadChar;
			break;
	}

	ds->type = type;

	ds->this = ds->init();

	if(ds->this == NULL) {
		return NULL; /* init failed */
 	}

	return ds;
}

/* returns the data structure's display name  */
char *getDataStructureDisplayName(DataStructureType type) {
	switch(type)
	{
		case dynamicBuffer:
			return "Dynamic Buyffer";
		case linkedList:
			return "Linked List";
		default :
			return NULL;
	}
}
