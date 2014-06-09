#ifndef _H3_MPOOL_H__
#define _H3_MPOOL_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *begin;	/* start pos */
	size_t len;	/* capacity */
	int index;	/* curIndex */
	int cflag;	/* clear flag */
} h3_mpool;

void h3_mpool_init(h3_mpool *pmp, char *begin, size_t len);
void *h3_mpool_malloc(h3_mpool *pmp, size_t mlen);
void h3_mpool_free(h3_mpool *pmp, void *p);
void h3_mpool_clear(h3_mpool *pmp);

#ifdef __cplusplus
}
#endif
#endif

