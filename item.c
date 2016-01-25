/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <stdlib.h>

#include "item.h"

void
item_destroy (ITEM *i)
{
	if (!i) {
		return;
	}

	// Nothing ITEM-specific to release

	object_destroy (&i->object);	// Destroy parent
}

void
item_display (ITEM *i, int indent)
{
	if (!i) {
		return;
	}

	printf ("%*s\033[1;36m%s\033[m\n", indent * 8, "", i->object.name);
}

ITEM *
item_create (ITEM *i)
{
	if (!i) {
		i = calloc (1, sizeof (ITEM));
		if (!i) {
			return NULL;
		}
	}

	OBJECT *o = &i->object;

	object_create (o);	// Construct parent

	o->type     = MAGIC_OBJECT;
	o->destroy  = (object_destroy_fn) item_destroy;
	o->display  = (object_display_fn) item_display;

	return i;
}

