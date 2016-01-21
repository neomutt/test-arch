#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"

void
email_release (EMAIL *e)
{
	if (!e) {
		return;
	}

	free (e->from);
	free (e->to);
	free (e->subject);

	item_release (&e->item);	// Release parent
}

EMAIL *
email_create (EMAIL *e)
{
	if (!e) {
		e = calloc (1, sizeof (EMAIL));
		if (!e) {
			return NULL;
		}
	}

	item_create (&e->item);	// Construct parent

	OBJECT *o = &e->item.object;

	o->type     = MAGIC_EMAIL;
	o->release  = (object_release_fn) email_release;

	return e;
}

