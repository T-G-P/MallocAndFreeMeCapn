#include "mallocMeCapn.h"

static char bigBlock[BLOCKSIZE];

static struct mementry *root;

void *mymalloc(unsigned int size, char* file, unsigned int line)
{

    //add print statements.
    static int initialized = 0;                                                       //initializing bigblock static struct mementry *root; struct mementry *p, *succ;
    struct mementry *p, *succ;
    if (!initialized)
    {
        root = (struct mementry *) bigBlock;
        root->prev = root->succ = 0;                                                //making prevoius and successors null
        root->size = BLOCKSIZE - sizeof(struct mementry);                           //size is blocksize minus mementry size
        root->isFree = 1;                                                           //flagging this to be freed.
        initialized = 1;                                                            //space has been initialized
    }
    p = root;                                                                       //pointing to the root
    do
    {
        if (p->size < size)                                                         //Is it too small?
            p = p->succ;                                                            //increment pointer to its next to find free space
        else if (p->isFree == 0)                                                    //Is it in use?
            p = p->succ;                                                            //keep moving it since it's not free
        else if (p->size < (size + sizeof(struct mementry)))                        //cannot insert new mem entry
        {
            p->isFree = 0;                                                          //too small to chop up
            return (char *) p + sizeof(struct mementry);
        }
        //big enough to chop up and return requested amount
        else                                                                        //Other blocks appended
        {
            //placing this  mementry struct passed p + the size of the struct p is pointing to + the size passed in
            succ = (struct mementry*) ((char*)p + sizeof(struct mementry) + size);
            succ->prev = p;
            succ->succ = p->succ;
            if (p->succ != 0)                                                      //if p's  successor is not null
                p->succ->prev = succ;                                              //p's successors prevoius is now the successor
            p->succ = succ;
            succ->size = p->size - sizeof(struct mementry) - size;                 //the successor takes up the size of p->size less the struct size minus the size passed in
            succ->isFree = 1;                                                      //this
            p->size = size;
            p->isFree = 0;
            return (char*)p + sizeof(struct mementry);
        }
    }while (p != 0);

    printf("Error at %s, line %d: Not enough memory to allocate this\n");

    return 0;
}
/*
void *mycalloc(unsigned int size, char* file, unsigned int line)
    void *data = mymalloc(size);
    memset(data,0,size);
    return data;
}
*/
void myfree(void * p, char* file, unsigned int line)
{
    //Need to show that this is bad memory
    //check if free is marked 0, is p = mempt+sizeof(mp)
    //if not calling it on valid pointer, call on
    //need to iterate through all mementry structs
    //to find good pointers for freeing
    //iterate through linked list

    if((char*)p < (char*)&bigBlock || (char*)p > (char*)(&bigBlock + BLOCKSIZE)){
        printf("Error at %s, line %d: Trying to free non-allocated memory\n", file, line);
        return;
    }

    struct mementry *ptr, *pred, *succ;
    char *start, *end;
    for(ptr = root; ptr != NULL; ptr = ptr->succ){
        //check if p is within this range
        start = (char*)ptr + sizeof(struct mementry);
        end = start+ptr->size;
        if(start == p){
            if(ptr->isFree == 1){
                printf("Error at %s, line %d: Double free\n", file, line);
                return;
            }

            if((pred = ptr->prev) != 0 && pred->isFree){
                pred->size += sizeof(struct mementry) + ptr->size;
                pred->succ = ptr->succ;
                if(ptr->succ != 0){
                    ptr->succ->prev = pred;
                }
            }else{
                ptr->isFree = 1;
                pred = ptr;
            }
            if((succ = ptr->succ) != 0 && succ->isFree){
                pred->size = sizeof(struct mementry) + succ->size;
                pred->succ = succ->succ;
                if(succ->succ != 0){
                    succ->succ->prev = pred;
                }
            }
            return;
        }
    }
    //if equal to end or between end, error
    //if we get to end of loop and haven't found pointer, error.
    //check for double free

    printf("Error at %s, line %d: Trying to free a pointer not returned by malloc\n", file, line);
    //ptr = (struct mementry*)((char*)p - sizeof(struct mementry));

}

int main()
{
    /*char* string1 = malloc(sizeof(char)*1);
    char* string2 = malloc(sizeof(char)*1);
    char* string3 = malloc(sizeof(char));
    free(string1);
    free(string2);
    free(string3);
    free(string3);*/ //this still doesn't work
    //malloc(sizeof(char) * 100000); catches frag/sat
    /*char* p = malloc(sizeof(char)); //catches midblock free
    free(p+1);*/
    /*char* p = malloc(sizeof(char)); //catches double free
    free(p);
    free(p);*/
    /*int *x = 5; //catches non-alloc
    free(x);*/
    return 0;
}
