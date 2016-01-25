/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

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

void
month_destroy (MONTH *m)
{
	if (!m) {
		return;
	}

	// Nothing MONTH-specific to release

	folder_destroy (&m->folder);	// Destroy parent
}

void
month_display (MONTH *m, int indent)
{
	if (!m) {
		return;
	}

	const char *months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	const char *tabs     = "\t\t\t\t\t\t\t\t\t\t";
	const char *istr     = tabs + 9 - indent;

	printf ("%s\033[1;32m%s\033[m\n", istr + 1, m->folder.container.object.name);

	printf ("%s\033[1;36;7m  %s %d  \033[m\n", istr, months[m->month - 1], m->year);

	printf ("\033[1;36m%s", istr);

	int event_list[31];
	memset (event_list, 0, sizeof (event_list));

	int i;
	for (i = 0; i < m->folder.num_items; i++) {
		EVENT *e = (EVENT*) m->folder.items[i];
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

	for (i = 0; i < m->folder.num_items; i++) {
		OBJECT *o = &m->folder.items[i]->object;
		o->display (o, indent + 1);
	}
}

MONTH *
month_create (MONTH *m)
{
	if (!m) {
		m = calloc (1, sizeof (MONTH));
		if (!m) {
			return NULL;
		}
	}

	folder_create (&m->folder);	// Construct parent

	OBJECT *o = &m->folder.container.object;

	o->type     = MAGIC_MONTH;
	o->destroy  = (object_destroy_fn) month_destroy;
	o->display  = (object_display_fn) month_display;

	return m;
}

