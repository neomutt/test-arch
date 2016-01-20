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

	int rc;
	OBJECT *o = (OBJECT*) obj;

	if (o->release) {
		rc = (*o->release) (o);
	} else {
		o->refcount--;
		rc = o->refcount;
		if (o->refcount < 1) {
			free (o);
		}
	}

	return rc;
}

