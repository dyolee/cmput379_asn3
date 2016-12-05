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
	int pageArray[128];
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

	printf ("hashIndex: %d, value: %d, address: %d, pageCount: %d \n", hashIndex, value, address, pageCount[pageNumber]);

	struct node *newnode = createNode(address, value, pageNumber);
	if (!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newnode;
	} else {
		newnode -> next = (hashTable[hashIndex].head);
		hashTable[hashIndex].head = newnode;
	}
}


int get (unsigned int address) {

	int value = 0;
	/* From hashtable.c, void searchInHash */
	return value;

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

	init (128, 1000);
	put (1, 1);
	put (20, 1);
	put (128, 1);
	put (3000, 1);

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