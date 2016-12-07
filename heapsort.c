// Reference http://quiz.geeksforgeeks.org/heap-sort/

// C++ program for implementation of Heap Sort
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

int psize;
int winsize;

// A utility function to swap two elements
void swap ( unsigned int a1, unsigned int a2 )
{
    // get the values at input addresses
    int v1 = get(a1);
    int v2 = get(a2);

    // put the value at swapped addresses
    put(a1, v2);
    put(a2, v1);
}
 
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(unsigned int arr, int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if ( l < n && ( get(arr+l) > get(arr+largest) ) )
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && get(arr+r) > get(arr+largest))
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(arr+i, arr+largest);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
void heapSort(unsigned int arr, int n)
{
    int i;
    // Build heap (rearrange array)
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(arr, arr+i);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
 
// A utility function to print contents of arr
void printArr( unsigned int arr, int n )
{
    // unsigned int addr;
    // for ( addr = arr; addr < arr+n; addr++ )
	// printf( "%d,\n", get(addr) );
}

void process () {
    /* This process function generates a number of integer */
    /* keys and sorts them using *heapsort*. */
    int n, i;
    unsigned int arr = 0; // starting address of array

    printf("How many numbers to be sorted? ");
    scanf ("%d", &n);
    // printf ("Sorting %1d keys\n", n);

    init (psize, winsize); // Fixed init to take command line arguments

    /* Generate the sorting problem */
    for (i = arr; i < n; i++) put (i, lrand48 ());

    /* Sort the numbers */
    heapSort(arr, n);

    /* Verify correctness of sort */
    // printf("Sorted array is \n");
    // printArr(arr, n);

    /* Show statistics */
    done ();
}
 
// Driver program
int main(int argc, char **argv)
{
    psize = atoi(argv[1]);
    winsize = atoi(argv[2]);
    process();
    return 0;
}
