#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Referenced: 
	http://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/ */


struct hash * hashTable = NULL;


struct node {
	unsigned int address;
	int value;
	struct node *next;
};


struct hash {
	struct node *head;
};


struct node * createNode (unsigned int address, int value) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof (struct node));
	newnode -> address = address;
	newnode -> value = value;
	newnode -> next = NULL;
	return newnode;
};


int pageSize;
int windowSize;
int totalAccess = 0;
int *pageCount;

void init (int psize, int winsize) {
	// do nothing
	pageSize = psize;
	windowSize = winsize;
	int pageArray[psize];
	pageCount = pageArray;
}



void put (unsigned int address, int value) {

	int hashIndex = 0;
	totalAccess ++;

	hashIndex = address%pageSize;
	pageCount[hashIndex]++;

	if (totalAccess == windowSize)
	{
		/* The number of instructions is equal to the windowSize. Do something */
	}

	/* From hashtable.c, void insertToHash would go here */
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