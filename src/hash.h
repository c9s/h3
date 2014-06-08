#ifndef  __ESERV_HASH_H__
#define  __ESERV_HASH_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "mempool.h"
#include <strings.h>

typedef struct _slist {
	void *key;
	void *value;
	struct _slist *next;
} ex_hashlist;

typedef struct {
	ex_hashlist **buckets;
	size_t size;
	ex_mpool *mpool;
	int (*hashfun)(const void *key);
	int (*hashcmp)(const void *lkey, const void *rkey);
} ex_hashmap;

void ex_hash_init(ex_hashmap* hm, ex_mpool *mp , size_t _size);
void ex_hash_clear(ex_hashmap *hm);

int ex_hash_add(ex_hashmap *hm, const void *key, const void *value);
void* ex_hash_find(const ex_hashmap *hm, const void *key);

int ex_hashfun_str(const char *s);

#ifdef __cplusplus
}
#endif
#endif

