#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include "item.h"

#define MAGIC_ARTICLE ((1 << 8) + MAGIC_ITEM)

typedef struct article_t {
	ITEM item;
} ARTICLE;

ARTICLE * article_create (void);

#endif // _ARTICLE_H_
