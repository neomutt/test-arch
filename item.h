#ifndef _ITEM_H_
#define _ITEM_H_

#include "object.h"

#define MAGIC_ITEM 6

typedef struct item_t {
	OBJECT object;
} ITEM;

ITEM * item_create  (ITEM *i);
void   item_destroy (ITEM *i);
void   item_display (ITEM *i, int indent);

#endif // _ITEM_H_
