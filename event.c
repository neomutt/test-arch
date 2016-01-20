#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "event.h"

static void
event_free (EVENT *e)
{
	if (!e) {
		return;
	}

	OBJECT *o = &e->item.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (e->item.name);
		free (e);
	}
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
	o->release  = (object_release_fn) event_free;

	return e;
}


