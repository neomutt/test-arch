#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"

void
email_destroy (EMAIL *e)
{
	if (!e) {
		return;
	}

	free (e->from);
	free (e->to);
	free (e->subject);

	item_destroy (&e->item);	// Destroy parent
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
	o->destroy  = (object_destroy_fn) email_destroy;

	return e;
}

