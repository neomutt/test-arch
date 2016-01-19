#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"

static void
contact_free (CONTACT *c)
{
	if (!c) {
		return;
	}

	OBJECT *o = &c->item.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (c->item.name);
		free (c);
	}
}

CONTACT *
contact_create (void)
{
	CONTACT *c = NULL;

	c = calloc (1, sizeof (CONTACT));
	if (!c) {
		return NULL;
	}

	OBJECT *o = &c->item.object;

	o->refcount = 1;
	o->type     = MAGIC_CONTACT;
	o->release  = (object_release_fn) contact_free;

	return c;
}

