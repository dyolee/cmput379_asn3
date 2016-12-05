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
FILE *csv;


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
	csv = fopen ("windowsize_output.csv", "w+");
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
				fprintf(csv, "Page %d had %d accesses, ", i, pageCount[i]);
				pageCount[i] = 0;
				totalAccess = 0;
			}
		}
		fprintf(csv, "\n");
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

	

}

int main(int argc, char const *argv[])
{
	// Will call the actual sorting algorithm
	// Commented for now because no sorting algorithm is specified yet
	// Rather, hardcoded into the main function

	// void process ();
	// init (128, 1000);
	// for (int i = 0; i < 10002; ++i)
	// {
	// 	put(1, 1);
	// 	put(129, 2);
	// 	if (i%2 == 0) {
	// 		put (257, 3);
	// 	}
	// }
}
