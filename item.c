#include <stdio.h>
#include <stdlib.h>

#include "item.h"

static int
item_release (ITEM *i)
{
	if (!i) {
		return -1;
	}

	OBJECT *o = &i->object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (i->name);
		free (i);
	}

	return rc;
}

void
item_display (ITEM *i, int indent)
{
	if (!i) {
		return;
	}

	printf ("%*s\033[1;36m%s\033[m\n", indent * 8, "", i->name);
}

ITEM *
item_create (void)
{
	ITEM *i = NULL;

	i = calloc (1, sizeof (ITEM));
	if (!i) {
		return NULL;
	}

	OBJECT *o = &i->object;
	o->refcount = 1;
	o->type     = MAGIC_ITEM;
	o->release  = (object_release_fn) item_release;
	o->display  = (object_display_fn) item_display;

	return i;
}

