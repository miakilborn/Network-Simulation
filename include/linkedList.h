/* 
Generic Linked List Header
Author: Mia Kilborn
Created on: January 15, 2013
Class: CIS 2750, Assignment 1
Adapted from linked list ADT developed by self in CIS 2520
*/

/*this list ADT requires a compare function to compare two data elements
used for returning matches when searching the list
The compare function must return 0 if the elements are considered equal, non-zero otherwise*/

#ifndef L_LIST
#define L_LIST

#include <stdio.h>
#include <stdlib.h>

/****************************/
/** LIST DATA DECLARATIONS **/
/****************************/

/*NOTE TO SELF - Jan 15 - These declarations may have to be moved (for style) into the .c file*/
typedef void* listDataPtr;

/*One node of linked list*/
typedef struct node
{
	listDataPtr data;
	struct node* next;
} listNode;

/*Dummy node at start of linked list*/
typedef struct dummy
{
	int length;
	listNode* head;
} listDummy;

/**********************************/
/** CREATE, DESTROY, ADD, DELETE **/
/**********************************/

/*Creation of list
 Creates the dummy node at the start of the linked list
 PRECONDITIONS: users passes a functon of the correct prototype that compares two elements of data in the list, this function is expected to return 0 if the two elementes are equal
 POSTCONDITIONS: pointer to list is returned
 Function Call: theList = createList(&destroyData);
*/
listDummy* createList();

/*
 destroy list - used to neatly destroy the entire linked list
 PRECONDITIONS: initialized dummy node is passed into function as a parameter
 POSTCONDITIONS: each element in the list is neatly destroyed, with it's value set to zero. The memory is free'd.
 Function Call: destroyList(myList);
 */
int destroyList(listDummy*);

/*
 initNode: iitializes a new node to be used in the linked list - the memory is allocated for the node, then the value passed in is set as the node's value
 PRECONDITIONS: none
 POSTCONDITIONS: a new node is initialized with the specified integer as the value of the node
 Function Call: myNode = initNode(someData);
 */
listNode* initNode(listDataPtr);

/**********************************/
/************** ADD ***************/
/**********************************/

/*
 addFront: given some data value, adds it to the front of the linked list - just behind the header node (which is a dummy and holds no value). The header then points to the newly added node, while it points to the next node in line.
 PRECONDITIONS: a list exists and is initialized, some data is passed in as a parameter
 POSTCONDITIONS: the list is modified to add the new node to the front of the list, returns 1 upon success, 0 else
 note: this function uses the initNode function
 Function call: addFront(myList, someData);
 */
int addFront (listDummy*, listDataPtr);

/*
 addBack: given some data value, adds it to the back of the linked list
 PRECONDITIONS: a list exists and is initialized, some data is passed in as a parameter to this function
 POSTCONDITIONS: the list is modified in the function to include the additional node at the back of this list
 	returns 1 for success, 0 otherwise
 note: this function uses initNode function
 Function call: addBack(myList, someData);
 */
int addBack(listDummy*, listDataPtr);

/**********************************/
/************* OTHER **************/
/**********************************/

/*
isRightSize: informs user of number of elements stored in list
PRECONDITIONS: list has been initialized
POSTCONDITIONS: returns number of elements in list
function call: int size = getLength(myList)
*/
int getLength(listDummy*);

/*
getHead: returns a pointer to the head of the linked list (to skip over the dummy)
PRECONDITIONS: list has been initialized
POSTCONDITIONS: a pointer to the first node in the linked list is returned
function call: listNode* theHead = getHead(theList);
*/
listNode* getHead(listDummy*);

/*
pop function used to make this act like a queue
removes from the front of the queue
*/
listNode* pop(listDummy*);

/*
push function
adds to the back
returns 1 on sucess, 0 otherwise
*/
int push(listDummy*, listDataPtr);

#endif /* L_LIST */
