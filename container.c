#include <stdio.h>
#include <stdlib.h>

#include "container.h"

void
container_release (CONTAINER *c)
{
	if (!c) {
		return;
	}

	int i;
	for (i = 0; c->children[i]; i++) {
		release (c->children[i]);
	}

	object_release (&c->object);
}

void
container_display (CONTAINER *c, int indent)
{
	if (!c) {
		return;
	}

	int i;
	for (i = 0; i < c->num_children; i++) {
		CONTAINER *child = c->children[i];

		object_display (&child->object, indent);
	}
}

CONTAINER *
container_create (CONTAINER *c)
{
	if (!c) {
		c = calloc (1, sizeof (CONTAINER));
		if (!c) {
			return NULL;
		}
	}

	OBJECT *o = &c->object;

	object_create (o);	// Construct parent

	o->type     = MAGIC_CONTAINER;
	o->release  = (object_release_fn) container_release;
	o->display  = (object_display_fn) container_display;

	return c;
}

int
container_add_child (CONTAINER *c, void *child)
{
	if (!c || !child) {
		return -1;
	}

	if (c->add_child && (c->add_child != (container_add_child_fn) container_add_child)) {
		c->add_child (c, child);
	} else {
		printf ("container_add_child\n");
	}

	return 1;
}
