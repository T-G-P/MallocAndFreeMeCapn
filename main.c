#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Programming behavior is not affected by preemption

static char blockSize[5000];
static Header base;     //empty list to get started
static Header *freep = NULL;    //start of free list

void *mallocMe(size_t size);

void freeMe(void *ptr);

void *mallocMe(size_t size){
    Header *p,

}

void freeMe(void *ptr){

}

