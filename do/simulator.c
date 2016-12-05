#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Referenced: 
	http://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/ */


struct hash * hashTable = NULL;


struct node {
	int pageNumber;
	unsigned int address;
	int value;
	struct node *next;
};


struct hash {
	struct node *head;
};


int pageSize;
int windowSize;
int totalAccess = 0;
int *pageCount;


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
	pageSize = psize;
	windowSize = winsize;
	int pageArray[33554431/psize];
	pageCount = pageArray;
	hashTable = (struct hash *) calloc (psize, sizeof(struct hash));
}



void put (unsigned int address, int value) {

	int hashIndex = 0;
	totalAccess ++;
	int pageNumber;

	hashIndex = address%pageSize;
	pageNumber = address/pageSize;
	pageCount[pageNumber] += 1;
	

	if (totalAccess == windowSize) {
		for (int i = 0; i < pageSize; ++i) {
			if (pageCount[i] > 0) {
				printf("Page %d: \t Accesses: %d\n", i, pageCount[i]);
				pageCount[i] = 0;
			}
		}
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

	int hashIndex = address%pageSize;
	struct node *myNode;
	myNode = hashTable[hashIndex].head;
	while (myNode != NULL) {
		if (myNode -> address == address) {
			return myNode -> value;
		}
		myNode = myNode -> next;
	}
	return myNode -> value;
}


void done() {

	/* Most likely, print statements for working set sizes will go here:
		from hashtable.c,void display() */

}

int main(int argc, char const *argv[])
{
	// Will call the actual sorting algorithm
	// Commented for now because no sorting algorithm is specified yet
	// Rather, hardcoded into the main function

	// void process ();

	// For testing purposes
	int i;
	init (128, 1000);
	put (1, 1);
	put (2, 2);
	put (3, 3);
	put (4, 4);
	put (129, 129);
	i = get (1);
	printf("%d\n", i);
	i = get (2);
	printf("%d\n", i);
	i = get (3);
	printf("%d\n", i);
	i = get (4);
	printf("%d\n", i);
	i = get (129);
	printf("%d\n", i);
	return 0;
}

/*int hashFunction (unsigned int address, int value) {

	int hashIndex = 0;

	totalAccess ++;
	// If totalAccess = winsize then do something

	printf ("%d %d %d \n", windowSize, totalAccess, pageSize);
	pageCount[0]++;
	printf("%d %d\n", pageCount[0], pageCount[1]);
	return hashIndex;
}*/