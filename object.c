#include <stdio.h>
#include <stdlib.h>

#include "object.h"

void
object_destroy (OBJECT *o)
{
	if (!o) {
		return;
	}

	free (o->name);
	free (o);
}

void
object_display (OBJECT *o, int indent)
{
	if (!o) {
		return;
	}

	printf ("%*sOBJECT: 0x%04x %p %s\n", indent * 8, "", o->type, (void*) o, o->name);
}

OBJECT *
object_create (OBJECT *o)
{
	if (!o) {
		o = calloc (1, sizeof (OBJECT));
		if (!o) {
			return NULL;
		}
	}

	o->refcount = 1;
	o->type     = MAGIC_OBJECT;
	o->destroy  = (object_destroy_fn) object_destroy;
	o->display  = (object_display_fn) object_display;

	return o;
}


int
addref (void *obj)
{
	if (!obj) {
		return -1;
	}

	OBJECT *o = obj;

	o->refcount++;

	return o->refcount;
}

int
release (void *obj)
{
	if (!obj) {
		return -1;
	}

	OBJECT *o = obj;

	o->refcount--;
	if (o->refcount > 0) {
		return o->refcount;
	}

	if (o->destroy) {
		(*o->destroy) (o);
	} else {
		object_destroy (o);
	}

	return 0;
}

void
display (void *obj, int indent)
{
	if (!obj) {
		return;
	}

	OBJECT *o = obj;

	if (o->display) {
		o->display (o, indent);
	} else {
		object_display (o, indent);
	}
}

