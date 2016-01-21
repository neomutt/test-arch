#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"

void
contact_release (CONTACT *c)
{
	if (!c) {
		return;
	}

	// Nothing CONTACT-specific to release

	item_release (&c->item);	// Release parent
}

CONTACT *
contact_create (CONTACT *c)
{
	if (!c) {
		c = calloc (1, sizeof (CONTACT));
		if (!c) {
			return NULL;
		}
	}

	item_create (&c->item);	// Construct parent

	OBJECT *o = &c->item.object;

	o->type     = MAGIC_CONTACT;
	o->release  = (object_release_fn) contact_release;

	return c;
}

