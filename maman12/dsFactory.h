/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 13/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 12 Question 1
-------------------------------------------------------------------------------
*/

#ifndef DSFACTORY_H
#define DSFACTORY_H

#include <stdio.h>
#include "dynamicBuffer.h"
#include "linkedList.h"

/* --- CONSTANTS ------------------------------------------ */

#define DSTYPE_LBOUND 	(1)
#define DSTYPE_UBOUND 	(2)

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef enum {
	dynamicBuffer = 1,
	linkedList = 2
} DataStructureType;

typedef void *(*DataStructureInitFn)();

typedef int (*DataStructureWriteCharFn)(void *, char);

typedef char (*DataStructureReadCharFn)(void *);

typedef struct {
	void *this;
	DataStructureType type;
	DataStructureInitFn init;
	DataStructureWriteCharFn writeChar;
	DataStructureReadCharFn readChar;
} DataStructure;

/* --- FUNCTION DECLARATIONS ------------------------------ */
/* 
return a pointer to an instanciated DataStructure of type argument 'type',
or NULL if a memory allocation error occured.
*/
void *buildDataStructure(DataStructureType type);
/* returns the data structure's display name  */
char *getDataStructureDisplayName(DataStructureType type);

#endif