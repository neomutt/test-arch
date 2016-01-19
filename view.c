#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

const int MAGIC_VIEW = 1001;

static void
view_free (VIEW *v)
{
	if (!v) {
		return;
	}

	OBJECT *o = &v->object;
	o->refcount--;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < v->num_sources; i++) {
			// printf ("freeing source %p\n", (void*) v->sources[i]);
			object_release (v->sources[i]);
		}

		free (v->name);
		free (v);
	}
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
	o->release  = (object_release_fn) view_free;

	return v;
}

int
view_add_child (VIEW *v, void *child)
{
	if (!v || !child) {
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
	int i;
	for (i = 0; i < v->num_sources; i++) {
		source_display (v->sources[i], indent + 1);
	}
}

