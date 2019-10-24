#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortedList.h"

struct SortedList * createSortedList() {
//return a new empty List
	struct SortedList *temp = (struct SortedList *) malloc(sizeof(struct SortedList));
	temp->head = NULL;
	return temp;
}

void insertSorted(struct SortedList *aList, char * s) {
//PRE: aList has been created and is sorted
//insert s into aList so it remains sorted
	struct SortedNode *temp = (struct SortedNode *) malloc(sizeof(struct SortedNode));
	struct SortedNode * temp1;
	temp->data = strdup(s);
	if (aList->head == NULL || strcmp(aList->head->data, s) < 0) {
		temp->next = aList->head;
		aList->head = temp;
		return;
	}
	temp1 = aList->head;
	while (temp1->next != NULL && strcmp(temp1->next->data, s) > 0) {
		temp1 = temp1->next;
	}
	temp->next = temp1->next;
	temp1->next = temp;
}

void deleteSorted(struct SortedList *aList, char * s) {
//PRE: aList has been created and is sorted
//remove all occurrences of s from aList
	struct SortedNode *temp;
	struct SortedNode *temp1;
	while (aList->head != NULL && strcmp(aList->head->data, s) == 0) {
		temp = aList->head;
		aList->head = aList->head->next;
		free(temp);
	}
	if (aList->head == NULL) return;
	//at this point the list is not empty and the first node does not contain s
	temp = aList->head;
	while (temp->next != NULL && strcmp(temp->next->data, s) >= 0) {
		if (strcmp(temp->next->data, s) == 0) {
			temp1 = temp->next;
			temp->next = temp->next->next;
			free(temp1);
		} else {
			temp = temp->next;
		}
	}
}

int findSorted(struct SortedList *aList, char * s) {
//PRE: aList has been created and is sorted
//return 1 if s is in aList otherwise return 0
	struct SortedNode *temp = aList->head;
	while (temp != NULL) {
		if (strcmp(temp->data,s) == 0) return 1;
		temp = temp->next;
	}
	return 0;
}


void destroySortedList(struct SortedList *aList) {
//PRE: aList has been created
//free space created for aList
	struct SortedNode *temp;
	struct SortedNode *temp1;
	temp = aList->head;
	while (temp != NULL) {
		temp1 = temp;
		temp = temp->next;
		free(temp1);
	}
	free(aList);	
}