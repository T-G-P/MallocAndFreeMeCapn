#ifndef MALLOCME_H
#define MALLOCME_H
#define NALLOC 1024

typedef long Align;     //for alignment to long boundary

union header {      //block header
    struct s{
        union header *ptr;      //next block if on free list
        unsigned size;          //size of this block
    };
    Align x;                    //force alignment of blocks
};

typedef union header Header;

static Header *morecore(unsigned);

void *mallocMe(size_t size);

void freeMe(void *ptr);

#endif
