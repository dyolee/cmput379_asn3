// Reference: http://www.geeksforgeeks.org/iterative-quick-sort/

// An iterative implementation of quick sort
#include <stdio.h>
#include <simulator.h>
 
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
 
/* This function is same in both iterative and recursive*/
int partition (unsigned int arr, int l, int h)
{
    int x = get(arr+h);
    int i = l-1;
 
    for (int j = l; j <= h-1; j++)
    {
        if (get(arr+j) <= x)
        {
            i++;
            swap(arr+i, arr+j);
        }
    }
    swap (arr+i+1, arr+h);
    return i+1;
}
 
/* A[] --> Array to be sorted, 
   l  --> Starting index, 
   h  --> Ending index */
void quickSortIterative (unsigned int arr, int l, int h)
{
    // Create an auxiliary stack
    //int stack[ h - l + 1 ];
    unsigned int stack = arr + h-l+1;
 
    // initialize top of stack
    int top = -1;
 
    // push initial values of l and h to stack
    // stack[ ++top ] = l;
    put(stack + (++top), l);
    // stack[ ++top ] = h;
    put(stack + (++top), h);
 
    // Keep popping from stack while is not empty
    while ( top >= 0 )
    {
        // Pop h and l
        h = get(stack - (top--));
        l = get(stack - (top--));
 
        // Set pivot element at its correct position
        // in sorted array
        int p = partition( arr, l, h );
 
        // If there are elements on left side of pivot,
        // then push left side to stack
        if ( p-1 > l )
        {
            // stack[ ++top ] = l;
            put(stack + (++top), l);
            // stack[ ++top ] = p - 1;
            put(stack + (++top), p-1);
        }
 
        // If there are elements on right side of pivot,
        // then push right side to stack
        if ( p+1 < h )
        {
            // stack[ ++top ] = p + 1;
            put(stack + (++top), p+1);
            // stack[ ++top ] = h;
            put(stack + (++top), h);
        }
    }
}
 
// A utility function to print contents of arr
void printArr( unsigned int arr, int n )
{
    unsigned int addr;
    for ( addr = arr; addr < arr+n; addr++ )
    printf( "%d", get(addr) );
}

void process () {
    /* This process function generates a number of integer */
    /* keys and sorts them using *heapsort*. */
    int n, i;
    unsigned int arr = 0; // starting address of array

    scanf ("%d", &n);
    printf ("Sorting %1d keys\n", n);

    init (128, 1000);

    /* Generate the sorting problem */
    for (i = arr; i < n; i++) put (i, lrand48 ());

    /* Sort the numbers */
    quickSortIterative(arr, n);

    /* Verify correctness of sort */
    printf("Sorted array is \n");
    printArr(arr, n);

    /* Show statistics */
    done ();
}
 
// Driver program to test above functions
int main()
{
    process();
    return 0;
}
