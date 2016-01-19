#ifndef _ITEM_H_
#define _ITEM_H_

#include "object.h"

extern const int MAGIC_ITEM;

typedef struct item_t {
	OBJECT object;
	char *name;
} ITEM;

ITEM * item_create (void);
void item_display (ITEM *i, int indent);

#endif // _ITEM_H_
