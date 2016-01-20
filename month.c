#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "event.h"
#include "folder.h"
#include "month.h"
#include "plugin.h"
#include "folder.h"
#include "view.h"

static int
month_release (MONTH *f)
{
	if (!f) {
		return -1;
	}

	OBJECT *o = &f->folder.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < f->folder.num_folders; i++) {
			object_release (f->folder.folders[i]);
		}

		for (i = 0; i < f->folder.num_items; i++) {
			object_release (f->folder.items[i]);
		}

		free (f->folder.name);
		free (f);
	}

	return rc;
}

static void
month_display (FOLDER *f, int indent)
{
	if (!f) {
		return;
	}

	const char *months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	const char *tabs     = "\t\t\t\t\t\t\t\t\t\t";
	const char *istr     = tabs + 9 - indent;

	MONTH *m = (MONTH*) f;

	printf ("%s\033[1;32m%s\033[m\n", istr + 1, f->name);

	printf ("%s\033[1;36;7m  %s %d  \033[m\n", istr, months[m->month - 1], m->year);

	printf ("\033[1;36m%s", istr);

	int event_list[31];
	memset (event_list, 0, sizeof (event_list));

	int i;
	for (i = 0; i < f->num_items; i++) {
		EVENT *e = (EVENT*) f->items[i];
		event_list[e->day - 1]++;
	}

	for (i = 1; i < 32; i++) {
		if (event_list[i - 1] == 0) {
			printf ("%2d ", i);
		} else {
			printf ("\033[7m%2d\033[0;1;36m ", i);
		}
		if ((i % 7) == 0) {
			printf ("\n%s", istr);
		}
	}
	printf ("\n\033[m\n");

	for (i = 0; i < f->num_items; i++) {
		OBJECT *o = &f->items[i]->object;
		o->display (o, indent + 1);
	}
}

MONTH *
month_create (void)
{
	MONTH *m = NULL;

	m = calloc (1, sizeof (MONTH));
	if (!m) {
		return NULL;
	}

	OBJECT *o = &m->folder.object;

	o->refcount = 1;
	o->type     = MAGIC_MONTH;
	o->release  = (object_release_fn) month_release;
	o->display  = (object_display_fn) month_display;

	return m;
}

int
month_add_child (MONTH *m, void *child)
{
	if (!m || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if (obj->type != MAGIC_EVENT) {
		printf ("can't add object:0x%04x to a month\n", obj->type);
		return 0;
	}

	FOLDER *f = &m->folder;

	object_addref (child);
	f->items[f->num_items] = child;
	f->num_items++;

	return 1;
}

