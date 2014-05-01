#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <"mallocMe.h">

//Programming behavior is not affected by preemption

static Header base;                     //empty list to get started
static Header *freep = NULL;            //start of free list

void *mallocMe(unsigned nbytes){
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header)+1;
    if ((prevp = freep) == NULL){       //no free list yet
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr){
        if(p->s.size >= nunits){        //big enough
            if(p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else{                       //allocates at tail end
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep)                 //wrapped around free list
            if ((p = morecore(nunits)) == NULL)
                return NULL;            //none left
}

static Header *morecore(unsigned nu){
    char *cp, *sbrk(int);
    Header *up;

    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)              //no space at all
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

void freeMe(void *ap){
   Header *bp, *p;

   bp = (Header *)ap
}
