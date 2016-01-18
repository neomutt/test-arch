#include <stdlib.h>

#include "object.h"

int
object_addref (void *obj)
{
	if (!obj) {
		return -1;
	}

	OBJECT *o = (OBJECT*) obj;
	o->refcount++;

	return o->refcount;
}

int
object_release (void *obj)
{
	if (!obj) {
		return -1;
	}

	OBJECT *o = (OBJECT*) obj;
	o->refcount--;

	int rc = o->refcount;
	if (o->refcount < 1) {
		if (o->release) {
			(*o->release) (o);
		} else {
			free (o);
		}
	}

	return rc;
}

