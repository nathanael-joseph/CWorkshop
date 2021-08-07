/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 28/06/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

/* ======================= NOT IN USE ================================ */

#ifndef NODES_H
#define NODES_H

/* --- CONSTANTS ------------------------------------------ */

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef struct singleLinkListNode SingleLinkListNode;

struct singleLinkListNode {
	SingleLinkListNode *next;
	String key;
	void *data; 
};

typedef struct doubleLinkedListNode DoubleLinkedListNode;

struct doubleLinkedListNode {
	DoubleLinkedListNode *next;
	DoubleLinkedListNode *previous;
	String key;
	void *data;
};

typedef struct binaryTreeNode BinaryTreeNode;

struct binaryTreeNode {
	BinaryTreeNode *parent;
	BinaryTreeNode *leftChild;
	BinaryTreeNode *rightChild;
	String key;
	void *data;
};

/* --- FUNCTION DECLARATIONS ------------------------------ */

#endif