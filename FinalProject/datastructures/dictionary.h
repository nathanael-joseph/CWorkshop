/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 30/06/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include "more_types.h"
#include "system_utils/memory_management.h"
#include "type_utils/string_utils.h"
#include "datastructures/singlelinkedlist.h"


/* --- CONSTANTS ------------------------------------------ */

#define DICTIONARY_INIT_SIZE (128) 

/* --- TYPE DEFINITIONS ----------------------------------- */


typedef struct dictionary Dictionary;


/* --- FUNCTION DECLARATIONS ------------------------------ */

/* 
	Returns a pointer to a new empty dictionary with a sepcified starting size. Size must be greater than 0.
	The Dictionary's array size (M) will double when N/M > 1. 
*/
void *Dictionary_init(unsigned int initialSize);

/* Frees the dictionary, but does not call free on value pointers. */
void Dictionary_free(void *dictionary);

/* Frees the dictionary, and calls callback(value) on each value before the entry is freed */
void Dictionary_freeWithCallback(void *dictionary, void (*callback)(void *value) );

/* Returns true if the dictionary contains the argmuent key, false otherwise. */
Boolean Dictionary_containsKey(void *dictionary, String key);

/* Adds a new key value pair to the dictionary. Will throw an error if a duplicate key is provided */
/* void Dictionary_add(String key, void *value, void *dictionary); -- use setvalue instead */

/* Updates the value for the argument key in the dictionary. If no such key exists, it will be created */
void Dictionary_setValue(void *dictionary, String key, void *value);

/* Returns the value pointer for the given key in the dictionary. Returns NULL if no such key exists */ 
void *Dictionary_getValue(void *dictionary, String key);

/* 
	Removes the entry in the hash table for the argument key, and returns its value pointer.
	Returns NULL if no matching key was found.
*/
void *Dictionary_removeKey(void *dictionary, String key);

/* returns the current size of the hastable array */
unsigned int Dictionary_getSize(void *dictionary);

/* returns the current number of keys in the dictionary */
unsigned int Dictionary_getCount(void *dictionary);

/* returns the number of elements in the hashtable devided by the size */
float Dictionary_getDensity(void *dictionary);

/* executes (*callback)(key, data) on each key valye pair in the dictionary */
void Dictionary_foreach(void *dictionary, 
						void (*callback)(String key, void *value, void *args), 
						void *args);




#endif