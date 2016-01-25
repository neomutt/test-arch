/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <stdlib.h>

#include "folder.h"
#include "item.h"

void
folder_destroy (FOLDER *f)
{
	if (!f) {
		return;
	}

	int i;
	for (i = 0; i < f->num_items; i++) {
		release (f->items[i]);
	}

	container_destroy (&f->container);	// Destroy parent
}

void
folder_display (FOLDER *f, int indent)
{
	if (!f) {
		return;
	}

	printf ("%*s\033[1;32m%s\033[m\n", indent * 8, "", f->container.object.name);

	if ((f->num_items == 0) && (f->container.num_children == 0)) {
		printf ("%*s\033[1;36m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		container_display (&f->container, indent + 1);

		int i;
		for (i = 0; i < f->num_items; i++) {
			display (f->items[i], indent + 1);
		}
	}
}

int
folder_add_child (FOLDER *f, void *child)
{
	if (!f || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xFF) == MAGIC_ITEM) {
		addref (child);
		f->items[f->num_items] = child;
		f->num_items++;
	} else {
		container_add_child (&f->container, child);
	}

	return 1;
}

FOLDER *
folder_create (FOLDER *f)
{
	if (!f) {
		f = calloc (1, sizeof (FOLDER));
		if (!f) {
			return NULL;
		}
	}

	container_create (&f->container);	// Construct parent

	OBJECT *o = &f->container.object;

	o->type     = MAGIC_FOLDER;
	o->destroy  = (object_destroy_fn) folder_destroy;
	o->display  = (object_display_fn) folder_display;

	CONTAINER *c = &f->container;

	c->add_child = (container_add_child_fn) folder_add_child;

	return f;
}

