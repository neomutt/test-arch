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

	OBJECT *o = &v->object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < v->num_sources; i++) {
			// printf ("freeing source %p\n", (void*) v->sources[i]);
			object_release (v->sources[i]);
		}

		free (v->name);
		free (v);
	}

	return rc;
}

VIEW *
view_create (void)
{
	VIEW *v = NULL;

	v = calloc (1, sizeof (VIEW));
	if (!v) {
		return NULL;
	}

	OBJECT *o = &v->object;
	o->refcount = 1;
	o->type     = MAGIC_VIEW;
	o->release  = (object_release_fn) view_release;

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
	v->sources[v->num_sources] = child;
	v->num_sources++;

	return 1;
}

void
view_display (VIEW *v, int indent)
{
	if (!v) {
		return;
	}

	printf ("%*s\033[1;31m%s\033[m\n", indent * 8, "", v->name);

	if (v->num_sources == 0) {
		printf ("%*s\033[1;33m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		int i;
		for (i = 0; i < v->num_sources; i++) {
			source_display (v->sources[i], indent + 1);
		}
	}
}

