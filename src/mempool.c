#include <stdio.h>
#include <stdlib.h>
#include "mempool.h"

void h3_mpool_init(h3_mpool *pmp, char *begin, size_t len)
{
	pmp->begin = begin;
	pmp->len = len;
	pmp->index = 0;
	pmp->cflag = 0;
}

void *h3_mpool_malloc(h3_mpool *pmp, size_t mlen)
{
	void *ret = NULL;

	size_t rIndex = pmp->index + mlen;
	if (rIndex > pmp->len) {
		ret = malloc(mlen);
		pmp->cflag = 1;
	}
	else {
		ret = pmp->begin + pmp->index;
		pmp->index = rIndex;
	}
	return ret;
}

void h3_mpool_free(h3_mpool *pmp, void *p)
{
	/* only perform free when allocated in heap */
	if (p < (void *) pmp->begin ||
	    p >= (void *) (pmp->begin + pmp->len)) {
		free(p);
	}
}

void h3_mpool_clear(h3_mpool *pmp)
{
	pmp->index = 0;
	pmp->cflag = 0;
}
