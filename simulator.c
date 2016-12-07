#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simulator.h"

#define FILENAME "wss_history.txt"

/* Referenced: 
	http://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/ */


struct hash * hashTable = NULL;
int pageSize;
int windowSize;
int totalAccess = 0;
int *pageCount;
int intervalCount = 0;
char filename[256];
FILE *txt;
FILE *stats;


/* Print function to print statistics to an output file */
void printStats (FILE *txt) {

	int wss = 0;

	// Iterate through page access tracker
	for (int i = 0; i < pageSize; ++i)
		if (pageCount[i] > 0) {
			// count accessed pages as part of the working set
			++wss;
			// reset stats for next window
			pageCount[i] = 0;
		}

	// reset stats for next window
	totalAccess = 0;

	fprintf(txt, "%d ", wss);
	fprintf(stats, "%d ", wss);
	fflush(txt);
	fflush(stats);
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
	txt = fopen (FILENAME, "w+");
	sprintf(filename, "%dx%d.txt", psize, winsize);
	stats = fopen (filename, "w+");
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
			pageCount[myNode -> pageNumber]++;
			return myNode -> value;
		}
		myNode = myNode -> next;
	}
	

	return 0;
}


void done() {

	txt = fopen(FILENAME, "r");
	int wss;
	int pageAccessCount = 0;
	double averageAccess;

	printf("Working Set Size History:\n");
	
	if (txt) {

		while (fscanf(txt, "%d ", &wss) == 1) {
			pageAccessCount += wss;
			printf("%d ", wss);
		}

		printf("\n");
		fclose(txt);
	}

	pageAccessCount -= intervalCount;
	averageAccess = ((double)pageAccessCount)/((double)intervalCount);
	printf("Average Working Set Size:\n%.5lf\n", averageAccess);
}