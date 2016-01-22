#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "view.h"

static int
view_destroy (VIEW *v)
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
		container_display (&v->container, indent + 1);
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
	o->destroy  = (object_destroy_fn) view_destroy;
	o->display  = (object_display_fn) view_display;

	return v;
}

