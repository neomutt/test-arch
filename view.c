#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "view.h"

static int
view_release (VIEW *v)
{
	if (!v) {
		return -1;
	}

	OBJECT *o = &v->container.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < v->container.num_children; i++) {
			// printf ("freeing source %p\n", (void*) v->sources[i]);
			release (v->container.children[i]);
		}

		free (o->name);
		free (v);
	}

	return rc;
}

void
view_display (VIEW *v, int indent)
{
	if (!v) {
		return;
	}

	printf ("%*s\033[1;31m%s\033[m\n", indent * 8, "", v->container.object.name);

	if (v->container.num_children == 0) {
		printf ("%*s\033[1;33m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		int i;
		for (i = 0; i < v->container.num_children; i++) {
			object_display (&v->container.children[i]->object, indent + 1);
		}
	}
}

VIEW *
view_create (VIEW *v)
{
	if (!v) {
		v = calloc (1, sizeof (VIEW));
		if (!v) {
			return NULL;
		}
	}

	container_create (&v->container);	// Construct parent

	OBJECT *o = &v->container.object;

	o->type     = MAGIC_VIEW;
	o->release  = (object_release_fn) view_release;
	o->display  = (object_display_fn) view_display;

	return v;
}

int
view_add_child (VIEW *v, void *child)
{
	if (!v || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xff) != MAGIC_SOURCE) {
		printf ("can't add object:0x%04x to a view\n", obj->type);
		return 0;
	}

	object_addref (child);
	v->container.children[v->container.num_children] = child;
	v->container.num_children++;

	return 1;
}

