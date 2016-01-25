/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "container.h"
#include "folder.h"

void
source_destroy (SOURCE *s)
{
	if (!s) {
		return;
	}

	int i;
	for (i = 0; i < s->num_items; i++) {
		release (s->items[i]);
	}

	container_destroy (&s->container);	// Destroy parent
}

void
source_display (SOURCE *src, int indent)
{
	if (!src) {
		return;
	}

	printf ("%*s\033[1;33m%s\033[m\n", indent * 8, "", src->container.object.name);

	if (src->container.num_children == 0) {
		printf ("%*s\033[1;32m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		int i;
		for (i = 0; i < src->num_items; i++) {
			display (src->items[i], indent + 1);
		}

		container_display (&src->container, indent + 1);
	}
}

int
source_add_child (SOURCE *src, void *child)
{
	if (!src || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xFF) == MAGIC_ITEM) {
		addref (child);
		src->items[src->num_items] = child;
		src->num_items++;
	} else {
		container_add_child (&src->container, child);
	}

	return 1;
}

SOURCE *
source_create (SOURCE *s)
{
	if (!s) {
		s = calloc (1, sizeof (SOURCE));
		if (!s) {
			return NULL;
		}
	}

	container_create (&s->container);	// Construct parent

	OBJECT *o = &s->container.object;

	o->type     = MAGIC_SOURCE;
	o->destroy  = (object_destroy_fn) source_destroy;
	o->display  = (object_display_fn) source_display;

	CONTAINER *c = &s->container;

	c->add_child = (container_add_child_fn) source_add_child;

	return s;
}

