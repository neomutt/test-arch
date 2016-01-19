#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"

static void
email_free (EMAIL *e)
{
	if (!e) {
		return;
	}

	OBJECT *o = &e->item.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (e->item.name);
		free (e->from);
		free (e->to);
		free (e->subject);
		free (e);
	}
}

EMAIL *
email_create (void)
{
	EMAIL *e = NULL;

	e = calloc (1, sizeof (EMAIL));
	if (!e) {
		return NULL;
	}

	OBJECT *o = &e->item.object;

	o->refcount = 1;
	o->type     = MAGIC_EMAIL;
	o->release  = (object_release_fn) email_free;

	return e;
}


