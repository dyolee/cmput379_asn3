#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simulator.h"

/* Referenced: 
	http://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/ */

struct hash * hashTable = NULL;
int pageSize;
int windowSize;
int totalAccess = 0;
int *pageCount;
int intervalCount = 0;
FILE *txt;


struct node * createNode (unsigned int address, int value, int pageNumber) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof (struct node));
	newnode -> pageNumber = pageNumber;
	newnode -> address = address;
	newnode -> value = value;
	newnode -> next = NULL;
	return newnode;
};

void init (int psize, int winsize) {
	// init globals
	pageSize = psize;
	windowSize = winsize;
	int pageArray[33554431/psize];
	pageCount = pageArray;
	hashTable = (struct hash *) calloc (psize, sizeof(struct hash));
	txt = fopen ("windowsize_output.txt", "w+");
}



void put (unsigned int address, int value) {

	int hashIndex = 0;
	totalAccess ++;
	int pageNumber;
	int intervalMessagePrinted = 0;

	hashIndex = address%pageSize;
	pageNumber = address/pageSize;
	pageCount[pageNumber] ++;
	

	if (totalAccess == windowSize) {
		intervalCount++;
		for (int i = 0; i < pageSize; ++i) {
			if (pageCount[i] > 0) {
				if (!intervalMessagePrinted) {
					fprintf(txt, "Interval %d: ", intervalCount);
					fflush(txt);
					intervalMessagePrinted = 1;
				}
				fprintf(txt, "%d ", i);
				fflush (txt);
				pageCount[i] = 0;
				totalAccess = 0;
			}
		}
		fprintf(txt, "\n");
		fflush (txt);
	}

	struct node *newnode = createNode(address, value, pageNumber);
	if (!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newnode;
	} else {
		newnode -> next = (hashTable[hashIndex].head);
		hashTable[hashIndex].head = newnode;
	}
}


int get (unsigned int address) {

	struct node *myNode;

	int hashIndex = address % pageSize;
	myNode = hashTable[hashIndex].head;

	while (myNode != NULL) {
		if (myNode -> address == address) {
			return myNode -> value;
		}
		myNode = myNode -> next;
	}

	return 0;
}


void done() {

	// int c;
	txt = fopen("windowsize_output.txt", "r");
    char x[1024];
    int pageAccessCount = 0;
    double averageAccess;
	
	if (txt) {
	    while (fscanf(txt, " %1023s", x) == 1) {
	    	if (strstr("Interval", x) == NULL) {
	    		pageAccessCount++;
	    		printf("%s ", x);
	    	}
	    	if (strstr("Interval", x)) {
	    		printf("\n");
	    		printf("%s ", x);
	    	}
	    }
	    printf("\n");
    	fclose(txt);
	}

	pageAccessCount -= intervalCount;
	averageAccess = ((double)pageAccessCount)/((double)intervalCount);
	printf("Average page accesses over execution time: %.2lf %d %d\n", averageAccess, pageAccessCount, intervalCount);
}