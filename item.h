#ifndef _ITEM_H_
#define _ITEM_H_

#include "object.h"

#define MAGIC_ITEM 4

typedef struct item_t ITEM;

typedef void (*item_display_fn) (ITEM *f, int indent);

typedef struct item_t {
	OBJECT object;
	char *name;
	item_display_fn display;
} ITEM;

ITEM * item_create (void);
void item_display (ITEM *i, int indent);

#endif // _ITEM_H_
