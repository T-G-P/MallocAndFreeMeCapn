
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

#define BLOCKSIZE 5000;
static char bigBlock[BLOCKSIZE];

struct mementry
{
    struct mementry *prev;
    struct mementry *succ;
    int isFree;
    int size;
};

void *mymalloc(int size)
{ static int initialized = 0;   //initializing bigblock static struct mementry *root; struct mementry *p, *succ;
    if (!initialized)
    {
        root = (struct mementry *) bigBlock;
        root->prev = root->succ = 0;        //making prevoius and successors null
        root->size = BLOCKSIZE - sizeof(struct mementry);   //size is blocksize minus mementry size
        root->isFree = 1;   //flagging this to be freed.
        initialized = 1;    //space has been initialized
    }
    p = root;             //pointing to the root
    do
    {
        if (p->size < size)         //Is it too small?
            p = p->succ;              //increment pointer to its next to find free space
        else if (p->isFree == 0)    //Is it in use?
            p = p->succ;              //keep moving it since it's not free
        else if (p->size < (size + sizeof(struct mementry)))    //cannot insert new mem entry
        {
            p->isFree = 0;            //too small to chop up
            return (char *) p + sizeof(struct mementry);
        }
        //big enough to chop up and return requested amount
        else  //Other blocks appended
        {
            //placing this  mementry struct passed p + the size of the struct p is pointing to + the size passed in
            succ = (struct mementry*) ((char*)p + sizeof(struct mementry) + size);
            succ->prev = p;
            succ->succ = p->succ;
            if (p->succ != 0)               //if p's  successor is not null
                p->succ->prev = succ;       //p's successors prevoius is now the successor
            p->succ = succ;
            succ->size = p->size - sizeof(struct mementry) - size;    //the successor takes up the size of p->size less the struct size minus the size passed in
            succ->isFree = 1;             //this
            p->size = size;
            p->isFree = 0;
            return (char*)p + sizeof(struct mementry);
        }

    }while (p != 0);

    return 0;
}

void myfree(void * p)
{
    struct mementry *ptr, *pred, *succ;

    ptr = (struct mementry*)((char*)p - sizeof(struct mementry));

    if (ptr->isFree == 1)
    {
        printf("That was freed before. (Double Free)!\n");
        return;
    }
    if ((pred = ptr->prev) != 0 && pred->isFree)
    {
        pred->size += sizeof(struct mementry) + ptr->size;  //Merge with predecessor
        pred->succ = ptr->succ;
        if (ptr->succ != 0)
            ptr->succ->prev = pred;

        printf("Freeing block %#x merging with predecessor new size is %d.\n", p, pred->size);
    }
    else
    {
        printf("Freeing block %#x.\n", p);
        ptr->isFree = 1;
        if (ptr->succ != 0)
            ptr->succ->prev = pred;
    }
    if ((succ = ptr-sdf>succ) != 0 && succ->isFree)
    {
        printf("pred: %d\n", ptr->isFree);
        pred = ptr;//pred needs to be assigned a value!!!
        pred->size += sizeof(struct mementry) + succ->size;  //Merge with successor
        pred->succ = succ->succ;
        if (succ->succ != 0)
            succ->succ->prev = pred;

        printf("Freeing block %#x merging with successor new size is %d.\n", p, pred->size);
    }
    return;
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
