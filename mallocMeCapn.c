#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)
//insert macro for line # here put macros in header
#define BLOCKSIZE 5000;
static char bigBlock[BLOCKSIZE];

struct mementry
{
    struct mementry *prev;
    struct mementry *succ;
    int isFree;
    int size;
};

struct mementry *root = 0;

void *mymalloc(int size)
{
    //add print statements.
    static int initialized = 0;                                                       //initializing bigblock static struct mementry *root; struct mementry *p, *succ;
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

    return 0;
}

void myfree(void * p)
{
    //Need to show that this is bad memory
    //check if free is marked 0, is p = mempt+sizeof(mp)
    //if not calling it on valid pointer, call on
    //need to iterate through all mementry structs
    //to find good pointers for freeing
    //iterate through linked list
    struct mementry *ptr = root;
    for(ptr = root; ptr !=NULL; ptr=ptr->succ){
        //check if p is within this range
        start (char*)ptr +sizeof(mementry)
        end = start+ptr->size
        //if equal to end or between end, error
        //if we get to end of loop and haven't found pointer, error.
        //check for double free
        //
    }



    ptr = (struct mementry*)((char*)p - sizeof(struct mementry));

    if (ptr->isFree == 1)
    {
        printf("That was freed before. (Double Free)!\n");
        return;
    }
}

int main()
{
    char* string1 = mymalloc(sizeof(char)*1);
    char* string2 = mymalloc(sizeof(char)*1);
    char* string3 = mymalloc(sizeof(char)*1);
    free(string1);
    free(string2);
    free(string3);
    free(string3);
    return 0;
}
