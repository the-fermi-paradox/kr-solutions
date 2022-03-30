#include <stdio.h>
#include <limits.h>
typedef long Align; /* for alignment to long boundary */

union header {      /* block header: */
  struct {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x;          /* force alignment of blocks */
};
typedef union header Header;

static Header base;
static Header *freep = NULL;

void *alloc(unsigned nbytes);
void *kalloc(unsigned nmemb, unsigned nbytes)
{
  char* x = alloc(nmemb * nbytes);
  if (!x)
    return NULL;

  for (int i = 0; i < nmemb * nbytes; ++i)
    *(x + i) = 0;
  return (void*) x;
}

int main(void)
{
#define ARRAY_SIZE 8
  char* p = kalloc(ARRAY_SIZE, CHAR_BIT * sizeof(char));
  for (char* x = p; x - p < ARRAY_SIZE; ++x)
    printf("%i\n", *p);
  int** j = kalloc(ARRAY_SIZE, CHAR_BIT * sizeof(int *));
  for (int** x = j; x - j < ARRAY_SIZE; ++x)
    printf("%p\n", *j);
}

static Header *morecore(unsigned);
void *alloc(unsigned nbytes)
{
  Header *p, *prevp;
  unsigned nunits;
  nunits = ((nbytes + sizeof(Header) - 1)/sizeof(Header)) + 1;
  /* no free list yet */
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base; /* point base to self */
    base.s.size = 0;
  }
  for (p = prevp->s.ptr; ; prevp= p, p = p->s.ptr) {
    /* Big enough ? */
    if (p->s.size >= nunits) {
      /* Exactly big enough? */
      if (p->s.size == nunits) 
        prevp->s.ptr = p->s.ptr; /* just use the pointer */
      else {
        p->s.size -= nunits;
        p += p->s.size; /* shift over size - x */
        p->s.size = nunits; /* size now x */
      }
      /* first free pointer is the last one we visited */
      freep = prevp;
      return (void *)(p + 1);
    }
    /* wrapped around free list ? */
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

#define NALLOC 1024

void afree(void *ap);
static Header *morecore(unsigned nu)
{
  void *cp, *sbrk(int);
  Header *up;
  if (nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header));
  if (cp == (void *) -1)
    return NULL;
  up = (Header *) cp;
  up->s.size = nu;
  afree((void *) (up + 1));
  return freep;
}

void afree(void *ap)
{
  Header *bp, *p;
  bp = (Header *)ap - 1; /* point to block header */
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; /* freed block at start or end of arena */

  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}
