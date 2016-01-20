#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"

static int
contact_release (CONTACT *c)
{
	if (!c) {
		return -1;
	}

	OBJECT *o = &c->item.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (c->item.name);
		free (c);
	}

	return rc;
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

	o->refcount     = 1;
	o->type         = MAGIC_CONTACT;
	o->release      = (object_release_fn) contact_release;
	c->item.display = (item_display_fn)   item_display;

	return c;
}

