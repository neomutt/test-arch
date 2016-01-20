#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "event.h"

static int
event_release (EVENT *e)
{
	if (!e) {
		return -1;
	}

	OBJECT *o = &e->item.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (e->item.name);
		free (e);
	}

	return rc;
}

EVENT *
event_create (void)
{
	EVENT *e = NULL;

	e = calloc (1, sizeof (EVENT));
	if (!e) {
		return NULL;
	}

	OBJECT *o = &e->item.object;

	o->refcount = 1;
	o->type     = MAGIC_EVENT;
	o->release  = (object_release_fn) event_release;

	return e;
}


