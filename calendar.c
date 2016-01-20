#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calendar.h"
#include "email.h"
#include "folder.h"
#include "month.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

static void
calendar_source_free (CALENDAR_SOURCE *s)
{
	if (!s) {
		return;
	}

	OBJECT *o = &s->source.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (s->source.name);
		free (s);
	}
}

CALENDAR_SOURCE *
calendar_source_create (void)
{
	CALENDAR_SOURCE *s = NULL;

	s = calloc (1, sizeof (CALENDAR_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_CALENDAR;
	o->release  = (object_release_fn) calendar_source_free;

	return s;
}

int
calendar_init (void)
{
	return 1;
}

SOURCE *
calendar_connect (void)
{
	CALENDAR_SOURCE *is = NULL;

	is = calendar_source_create();
	if (!is) {
		return NULL;
	}

	SOURCE *s = &is->source;

	s->object.type = MAGIC_CALENDAR;
	s->name        = strdup ("calendar");

	MONTH_FOLDER *m1 = month_folder_create();

	m1->folder.name = strdup ("personal");

	source_add_child (s, &m1->folder);

	object_release (m1);

	return s;
}

int
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

void
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


