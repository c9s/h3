#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "hash.h"

static int hh_hashcmp_str(const char *s1, const char *s2)
{
	return (0 == strcmp(s1, s2));
}

void hh_hash_init(hh_hashmap *hm, h3_mpool *mp, size_t _size)
{
	assert(mp != NULL);
	hm->mpool = mp;
	hm->buckets = (hh_hashlist **)
		h3_mpool_malloc(mp,
		                sizeof(long) * _size);
	memset(hm->buckets, 0, sizeof(long) * _size);
	hm->size = _size;

	hm->hashcmp = (void *) hh_hashcmp_str;
	hm->hashfun = (void *) hh_hashfun_str;
}

void hh_hash_clear(hh_hashmap *hm)
{
	hh_hashlist *nl, *cl;
	size_t i;

	do {
		if (hm->mpool == NULL || hm->mpool->cflag == 0)
			break;
		for (i = 0 ; i < hm->size ; ++i) {
			cl = hm->buckets[i];
			while (cl != NULL) {
				nl = cl->next;
				h3_mpool_free(hm->mpool, cl);
				cl = nl;
			}
		}
		h3_mpool_free(hm->mpool, hm->buckets);
	} while (0);

	memset(hm, 0, sizeof(*hm));
}

int hh_hash_add(hh_hashmap *hm, const void *key, const void *value)
{
	int pos = hm->hashfun(key) % hm->size;
	hh_hashlist *nhl = (hh_hashlist *)
		h3_mpool_malloc(hm->mpool,
		                sizeof(hh_hashlist));

	nhl->key = (void *) key, nhl->value = (void *) value;
	nhl->next = hm->buckets[pos];
	hm->buckets[pos] = nhl;

	return pos;
}

void* hh_hash_find(const hh_hashmap *hm, const void *key)
{
	int pos = hm->hashfun(key) % hm->size;
	hh_hashlist *nlh = hm->buckets[pos];
	void *ret = NULL;
	while (nlh != NULL) {
		if (hm->hashcmp(nlh->key, key)) {
			ret = nlh->value;
			break;
		}
		nlh = nlh->next;
	}
	return ret;
}

int hh_hashfun_str(const char *s)
{
	int even , odd;
	int i = 0;
	int mask = 0x1F;
	int ret;
	even = odd = 0;
	while (*s != '\0') {
		if (i & 1) {
			odd ^= *s;
		}
		else {
			even ^= *s;
		}
		++s;
		++i;
	}
	ret = even & mask;
	ret <<= 5;
	ret += (odd & mask);
	return ret;
}
