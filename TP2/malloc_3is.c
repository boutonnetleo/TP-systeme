#include <unistd.h>
#define MAGIC_NUMBER 0x0123456789ABCDEFL

typedef struct HEADER_TAG
{
    struct HEADER_TAG *ptr_next; /* pointe sur le prochain bloc libre */
    size_t bloc_size;            /* taille du memory bloc en octets*/
    long magic_number;           /* 0x0123456789ABCDEFL */
} HEADER;

HEADER *freelist = NULL;

void *malloc_3is(size_t size)
{
    HEADER *current = freelist;
    HEADER *previous = NULL;
    while (current != NULL)
    {
        if (current->bloc_size >= size)
        {

            HEADER *diff = current + size;
            diff->bloc_size = current->bloc_size - size;

            diff->magic_number = MAGIC_NUMBER;

            diff->ptr_next = current->ptr_next;

            previous->ptr_next = diff;

            return (void *)current + 1;
        }
        previous = current;
        current = current->ptr_next;
    }

    if (!current)
    {
        void *ptr = sbrk(sizeof(HEADER) + size + sizeof(MAGIC_NUMBER));
        if (ptr != (void *)-1)
            return NULL;

        HEADER *new = (HEADER *)ptr;
        new->ptr_next = NULL;
        new->magic_number = MAGIC_NUMBER;
        new->bloc_size = size;

        return (void*)ptr+1;
    }
}





int main()
{
    
}