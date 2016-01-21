#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "container.h"
#include "folder.h"

void
source_release (SOURCE *s)
{
	if (!s) {
		return;
	}

	int i;
	for (i = 0; i < s->num_items; i++) {
		release (s->items[i]);
	}

	container_release (&s->container);	// Release parent
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
			object_display (&src->items[i]->object, indent + 1);
		}

		for (i = 0; i < src->container.num_children; i++) {
			object_display (&src->container.children[i]->object, indent + 1);
		}
	}
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
	o->release  = (object_release_fn) source_release;
	o->display  = (object_display_fn) source_display;

	return s;
}

int
source_add_child (SOURCE *src, void *child)
{
	if (!src || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xff) == MAGIC_FOLDER) {
		object_addref (child);
		src->container.children[src->container.num_children] = child;
		src->container.num_children++;
	} else if ((obj->type & 0xff) == MAGIC_ITEM) {
		object_addref (child);
		src->items[src->num_items] = child;
		src->num_items++;
	} else {
		printf ("can't add object:0x%04x to a source\n", obj->type);
		return 0;
	}

	return 1;
}

