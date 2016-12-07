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


/* Print function to print statistics to an output file */
void printStats (FILE *txt) {
	int intervalMessagePrinted = 0;
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


/* Function to create a new node in the linked list and return that node */
struct node * createNode (unsigned int address, int value, int pageNumber) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof (struct node));
	newnode -> pageNumber = pageNumber;
	newnode -> address = address;
	newnode -> value = value;
	newnode -> next = NULL;
	return newnode;
};

/* Initializing the exeriment. sets pageSize, windowSize, and creates an array
	to simulate accesses to pages */
void init (int psize, int winsize) {
	// init globals
	pageSize = psize;
	windowSize = winsize;
	int pageArray[33554431/psize];
	pageCount = pageArray;
	hashTable = (struct hash *) calloc (psize, sizeof(struct hash));
	txt = fopen ("windowsize_output.txt", "w+");
}



/* Function to insert a variable in the hash table according to their (32-bit) address */
void put (unsigned int address, int value) {

	int hashIndex = 0;
	int pageNumber;

	totalAccess ++;
	
	if (totalAccess == windowSize) {
		intervalCount++;
		printStats(txt);
	}

	/* hashIndex is determined by the modulo between address and pagesize */
	hashIndex = address%pageSize;
	/* PageNumber is determined by taking the floor of address/pageSize */
	pageNumber = address/pageSize;
	pageCount[pageNumber] ++;
	
	/* When totalAccess (number of store instructions) is equal to the windowsize then 
		record which pages were accessed at which intervals */

	/* Create a new node */
	struct node *newnode = createNode(address, value, pageNumber);
	/* The hashIndex does not exist from before. Then create a new hashIndex. 
		Make the new node the head of this new hashIndex */
	if (!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newnode;
	} else {
		/* The hashIndex exists from before. Great! Now attach the new 
		element to the linked list */
		newnode -> next = (hashTable[hashIndex].head);
		hashTable[hashIndex].head = newnode;
	}


}


/* Function to search for a value stored at an address. Takes only an 
	address as an argument */
int get (unsigned int address) {

	struct node *myNode;

	totalAccess++;

	if (totalAccess == windowSize) {
		intervalCount++;
		printStats(txt);
	}

	/* Calculate the hashIndex and search for that index */
	int hashIndex = address % pageSize;
	myNode = hashTable[hashIndex].head;

	/* Search through the linked list at the hashIndex to find the value */
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
	printf("Average page accesses over execution time: %.5lf %d %d\n", averageAccess, pageAccessCount, intervalCount);
}