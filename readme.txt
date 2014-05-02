Eric Bronner && Tobias Perelstein
pa6 readme

Malloc:
Meat of the code taken from Prof Russell's lecture. Root of the array made
global, added a print statement to detect when no allocateable memory is
available, or just not enough of it. This error checks for fragmentation and
saturation.

Free:
Meat of the code taken from Prof Russell's lecture. Function now loops through
the linked list of memEntries to make sure it can find a match and that the
input is good memory. Checks the isFree flag before freeing to detect double
free. Checks if the address of the pointer to be freed is within the array's
memory addresses to detect if the pointer was never allocated. If it cannot
find the pointer through the loop, realizes that it is trying to free a
pointer not returned from malloc, prints an error.

Calloc:
Calls malloc, using nmembs * size as the size. Uses bzero to zero the returned
array, then returns it. 
