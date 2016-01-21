#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "container.h"
#include "item.h"

#define MAGIC_SOURCE 4

typedef struct source_t SOURCE;

typedef struct source_t {
	CONTAINER container;
	int num_items;
	ITEM *items[10];
} SOURCE;

SOURCE * source_create    (SOURCE *s);
void     source_release   (SOURCE *s);
int      source_add_child (SOURCE *s, void *child);
void     source_display   (SOURCE *s, int indent);

#endif // _SOURCE_H_
