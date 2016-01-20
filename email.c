#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"

static int
email_release (EMAIL *e)
{
	if (!e) {
		return -1;
	}

	OBJECT *o = &e->item.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (e->item.name);
		free (e->from);
		free (e->to);
		free (e->subject);
		free (e);
	}

	return rc;
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

	o->refcount     = 1;
	o->type         = MAGIC_EMAIL;
	o->release      = (object_release_fn) email_release;
	e->item.display = (item_display_fn)   item_display;

	return e;
}

