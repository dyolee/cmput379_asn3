#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Used code from: 
	http://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/ */

struct hash * hashTable = NULL;


struct node {
	unsigned int address;
	int value;
	struct node *next;
}


struct hash {
	struct node *head;
}


struct node * createNode (unsigned int address, int value) {
	struct node *newnode;
	newnode = (struct node *) malloc (sizeof (struct node));
	newnode -> address = address;
	newnode -> value = value;
	newnode -> next = NULL;
	return newnode;
}


void init (int psize, int winsize) {

	// do nothing

}


void put (unsigned int address, int value) {

	/* From hashtable.c, void insertToHash */

}


int get (unsigned int address) {

	int value;
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

	return 0;
}