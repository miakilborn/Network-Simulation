/* 
Generic Linked List C File
Author: Mia Kilborn
Created on: January 15, 2013
Class: CIS 2750, Assignment 1
Adapted from linked list ADT developed by self in CIS 2520

IMPROVEMENTS TO BE MADE 
1. ITERATOR!!!!
2. Delete node given delete function to destroy that node's data
3. Change nature of comparison function to be passed in as a parameter to the function it is used in, not list as a whole
*/

/*this list ADT requires a compare function to compare two data elements
used for returning matches when searching the list*/

#include "linkedList.h"

/**********************************/
/******* CREATE and DESTROY *******/
/**********************************/

listDummy* createList()
{
	listDummy* dummy = NULL;
	dummy = malloc(sizeof(listDummy));
	dummy->head=NULL;
	dummy->length = 0;
	return dummy;
}

int destroyList(listDummy* theList)
{
	
	listNode* current;
	listNode* temp;

	if(theList->head == NULL){
		/*the list is empty*/
		theList->length=0;
		free(theList);
		return 1;
	}

	current = theList->head;

	while(current!=NULL){
		temp=current;
		current=temp->next;
		free(temp);
	}

	/*current will be set to null at the end of the above while loop*/
	/*destroy the dummy node*/

	theList->length=0;
	free(theList);
	return 1;
}

listNode* initNode(listDataPtr theData)
{
	listNode* newNode = NULL;
	newNode = malloc(sizeof(listNode));
	
	if(newNode==NULL){
		return NULL;
	}

	newNode->data = theData;
	newNode->next=NULL;

	return newNode;
}

/**********************************/
/********* ADD and REMOVE *********/
/**********************************/

int addFront (listDummy* theList, listDataPtr newData){
	listNode* newNode;
	newNode = initNode(newData);
	
	if (newNode==NULL){
		return 0;
	}

	newNode->next = theList->head;
	theList->head = newNode;
	theList->length++;

	return 1;
}

int addBack(listDummy* theList, listDataPtr newData){
	listNode* temp; /*iterator for list*/
	listNode* newNode;
	temp = theList->head;
	newNode = initNode(newData);

	if(newNode==NULL){
		return 0;
	}

	if(theList->head==NULL){
		theList->head = newNode;
	}

	else{

		if(temp->next!=NULL){
			/*loop to end of list*/
			while(temp->next!=NULL){
				temp=temp->next;
			}
		}
		temp->next = newNode;
	}
	theList->length++;

	return 1;
}

int getLegth(listDummy* theList){
	return theList->length;
}

listNode* getHead(listDummy* theList){
	listNode* theHead;
	theHead = theList->head;
	return theHead;
}

listNode* pop(listDummy* theList){
	listNode* theHead = theList->head;
	theList->head = theHead->next;
	theList->length --;
	return theHead;

}

int push(listDummy* theList, listDataPtr theData){
	return addBack(theList, theData);
}
