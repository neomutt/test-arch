#ifndef _ITEM_H_
#define _ITEM_H_

#include "object.h"

typedef struct item_t {
	OBJECT object;
	char *name;
} ITEM;

void item_free (ITEM *i);
void item_display (ITEM *i, int indent);

#endif // _ITEM_H_
