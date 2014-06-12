#ifndef  _H3_HASH_H__
#define  _H3_HASH_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "mempool.h"

typedef struct _slist {
	void *key;
	void *value;
	struct _slist *next;
} hh_hashlist;

typedef struct {
	hh_hashlist **buckets;
	size_t size;
	h3_mpool *mpool;
	int (*hashfun)(const void *key);
	int (*hashcmp)(const void *lkey, const void *rkey);
} hh_hashmap;

void hh_init(hh_hashmap* hm, h3_mpool *mp , size_t _size);
void hh_clear(hh_hashmap *hm);

int hh_add(hh_hashmap *hm, const void *key, const void *value);
void* hh_find(const hh_hashmap *hm, const void *key);

int hh_hashfun_str(const char *s);

#ifdef __cplusplus
}
#endif
#endif

