#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "event.h"

void
event_destroy (EVENT *e)
{
	if (!e) {
		return;
	}

	// Nothing EVENT-specific to release

	item_destroy (&e->item);	// Destroy parent
}

void
event_display (ITEM *i, int indent)
{
	if (!i) {
		return;
	}

	EVENT *e = (EVENT*) i;

	printf ("%*s\033[1;36m%2d %s\033[m\n", indent * 8, "", e->day, i->object.name);
}

EVENT *
event_create (EVENT *e)
{
	if (!e) {
		e = calloc (1, sizeof (EVENT));
		if (!e) {
			return NULL;
		}
	}

	item_create (&e->item);	// Construct parent

	OBJECT *o = &e->item.object;

	o->type     = MAGIC_EVENT;
	o->destroy  = (object_destroy_fn) event_destroy;
	o->display  = (object_display_fn) event_display;

	return e;
}

