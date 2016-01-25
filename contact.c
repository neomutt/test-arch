/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"

void
contact_destroy (CONTACT *c)
{
	if (!c) {
		return;
	}

	// Nothing CONTACT-specific to release

	item_destroy (&c->item);	// Destroy parent
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
	o->destroy  = (object_destroy_fn) contact_destroy;

	return c;
}

