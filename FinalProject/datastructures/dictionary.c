/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 31/06/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#include "datastructures/dictionary.h"

/* --- PRIVATE STRUCT/TYPE DEFINITIONS ------------------------------ */

struct dictionary {
	unsigned int size;
	unsigned int count;

	SingleLinkedList **hashtable;
};

/* --- STATIC FUNCTION DEFINITIONS ---------------------------------- */

/* 
	callback function for SingleLinkedList_foreach( ...)
	expects pointer : (*callback)(String key, void *data,void *args)
 */
static void addNodeToDictionary_callback(String key, void *data, void *dict) {
	Dictionary_setValue(dict, key, data);	
} 

/* Doubles the dicitionary's size */
static void Dictionary_grow(void *dict) {
	Dictionary *currentDict, *tempDict;
	SingleLinkedList *currentList;
	SingleLinkedList **tempHashtable;
	unsigned int i;

	currentDict = dict;
	tempDict = Dictionary_init(currentDict->size*2);

	for(i = 0; i < currentDict->size; i++) {
		currentList = *(currentDict->hashtable + i);
		SingleLinkedList_foreach(currentList, addNodeToDictionary_callback, tempDict);
	}

	tempHashtable = tempDict->hashtable;
	tempDict->hashtable = currentDict->hashtable;
	tempDict->size = currentDict->size;
	currentDict->hashtable = tempHashtable;

	Dictionary_free(tempDict); 

	currentDict->size *= 2;
}

/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* 
	Returns a pointer to a new empty dictionary with a sepcified starting size. Size must be greater than 0.
	The Dictionary's array size (M) will double when N/M > 1. 
*/
void *Dictionary_init(unsigned int initialSize) {
	unsigned int i; 

	Dictionary *dict = malloc(sizeof(*dict));

	dict->hashtable = calloc(initialSize, sizeof(*(dict->hashtable)));
	dict->size = initialSize;
	dict->count = 0;

	for(i = 0; i < dict->size; i++) {
		*(dict->hashtable + i) = SingleLinkedList_init();	
	}

	return dict;
}

/* Frees the dictionary, but does not call free on value pointers. */
void Dictionary_free(void *dictionary) {
	Dictionary_freeWithCallback(dictionary, NULL);
}

/* Frees the dictionary, and calls callback(value) on each value before the entry is freed */
void Dictionary_freeWithCallback(void *dictionary, void (*callback)(void *value) ) {
	Dictionary *dict = dictionary;
	unsigned int i;

	for(i = 0; i < dict->size; i++) {
		SingleLinkedList_freeWithCallback(*(dict->hashtable + i), callback);	
	}

	free(dict->hashtable);
	free(dict);
}


/* Returns true if the dictionary contains the argmuent key, false otherwise. */
Boolean Dictionary_containsKey(void *dictionary, String key) {
	Dictionary *dict = dictionary;
	
	unsigned int hashcode = String_hash(key, dict->size);

	return SingleLinkedList_containsKey(*(dict->hashtable + hashcode), key);
}

/* Adds a new key value pair to the dictionary. Will throw an error if a duplicate key is provided */
/* void Dictionary_add(String key, void *value, void *dictionary); -- use setvalue instead */

/* Updates the value for the argument key in the dictionary. If no such key exists, it will be created */
void Dictionary_setValue(void *dictionary, String key, void *value) {
	Dictionary *dict = dictionary;
	unsigned int hashcode = String_hash(key, dict->size);

	/* if no nodes in the list were updated */
	if (!SingleLinkedList_findAndReplaceByKey(*(dict->hashtable + hashcode), key, value)) {
		SingleLinkedList_insert(*(dict->hashtable + hashcode), key, value);
		dict->count++;

		if (Dictionary_getDensity(dict) > 1) {
			Dictionary_grow(dict);
		}
	}

}

/* Returns the value pointer for the given key in the dictionary. Returns NULL if no such key exists */ 
void *Dictionary_getValue(void *dictionary, String key) {	
	Dictionary *dict = dictionary;
	
	unsigned int hashcode = String_hash(key, dict->size);	

	return SingleLinkedList_getByKey(*(dict->hashtable + hashcode), key );
}

/* 
	Removes the entry in the hash table for the argument key, and returns its value pointer.
	Returns NULL if no matching key was found.
*/
void *Dictionary_removeKey(void *dictionary, String key) {
	Dictionary *dict = dictionary;
	
	void *value;
	unsigned int hashcode = String_hash(key, dict->size);	

	value = SingleLinkedList_removeFirstByKey(*(dict->hashtable + hashcode), key);

	if(value) {
		dict->count--;
	}

	return value;
}

/* returns the current size of the hastable array */
unsigned int Dictionary_getSize(void *dictionary) {
	Dictionary *dict = dictionary;
	return dict->size;
}

/* returns the current number of keys in the dictionary */
unsigned int Dictionary_getCount(void *dictionary) {
	Dictionary *dict = dictionary;
	return dict->count;
}

/* returns the number of elements in the hashtable devided by the size */
float Dictionary_getDensity(void *dictionary) {
	Dictionary *dict = dictionary;
	return (float)dict->count/dict->size;
}

/* executes (*callback)(key, data) on each key valye pair in the dictionary */
void Dictionary_foreach(void *dictionary, 
						void (*callback)(String key, void *value, void *args), 
						void *args) {

	Dictionary *dict = dictionary;
	SingleLinkedList *currentList;
	unsigned int i;


	for(i = 0; i < dict->size; i++) {
		currentList = *(dict->hashtable + i);
		SingleLinkedList_foreach(currentList, callback, args);
	}
}


