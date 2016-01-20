#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calendar.h"
#include "email.h"
#include "event.h"
#include "folder.h"
#include "month.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

static int
calendar_release (CALENDAR_SOURCE *s)
{
	if (!s) {
		return -1;
	}

	OBJECT *o = &s->source.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < s->source.num_folders; i++) {
			object_release (s->source.folders[i]);
		}

		for (i = 0; i < s->source.num_items; i++) {
			object_release (s->source.items[i]);
		}

		free (s->source.name);
		free (s);
	}

	return rc;
}

static CALENDAR_SOURCE *
calendar_create (void)
{
	CALENDAR_SOURCE *s = NULL;

	s = calloc (1, sizeof (CALENDAR_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_CALENDAR;
	o->release  = (object_release_fn) calendar_release;

	return s;
}

static int
calendar_init (void)
{
	return 1;
}

static SOURCE *
calendar_connect (void)
{
	CALENDAR_SOURCE *is = NULL;

	is = calendar_create();
	if (!is) {
		return NULL;
	}

	SOURCE *s = &is->source;

	s->object.type = MAGIC_CALENDAR;
	s->name        = strdup ("calendar");

	MONTH *m1 = month_create();

	m1->folder.name = strdup ("personal");
	m1->year        = 2016;
	m1->month       = 1;

	EVENT *e1 = event_create();
	EVENT *e2 = event_create();
	EVENT *e3 = event_create();

	e1->item.name = strdup ("Meet Jim");
	e2->item.name = strdup ("Bob's birthday");
	e3->item.name = strdup ("Dave in town");

	e1->day = 7;
	e2->day = 12;
	e3->day = 23;

	month_add_child (m1, e1);
	month_add_child (m1, e2);
	month_add_child (m1, e3);

	object_release (e1);
	object_release (e2);
	object_release (e3);

	source_add_child (s, &m1->folder);

	object_release (m1);

	return s;
}

static int
calendar_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'e') && (name[0] <= 'h')) {
		// printf ("calendar config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
calendar_disconnect (void)
{
}

PLUGIN calendar_plugin = {
	MAGIC_CALENDAR,
	"calendar",
	calendar_init,
	calendar_connect,
	calendar_disconnect,
	calendar_config_item
};


