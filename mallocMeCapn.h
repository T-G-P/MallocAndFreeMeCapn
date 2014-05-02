#ifndef mallocMeCapn_H
#define mallocMeCapn_H
#include <stdio.h>
#include <stdlib.h>
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define calloc(x) mycalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)
#define BLOCKSIZE 5000

struct mementry
{
    struct mementry *prev;
    struct mementry *succ;
    int isFree;
    int size;
};

void *mymalloc(unsigned int, char*, unsigned int);

//void *mycalloc(unsigned int, char*, unsigned int);

void myfree(void *, char *, unsigned int);

#endif
