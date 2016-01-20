#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
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

	printf ("%*s\033[1;32m%s\033[m\n", indent * 8, "", f->name);

	printf ("%*s\033[1;36m     January 2016   \033[m\n", (indent + 1) * 8, "");
	printf ("%*s\033[1;36m 1  2  3  4  5  6  7\033[m\n", (indent + 1) * 8, "");
	printf ("%*s\033[1;36m 8  9 10 11 12 13 14\033[m\n", (indent + 1) * 8, "");
	printf ("%*s\033[1;36m15 16 17 18 19 20 21\033[m\n", (indent + 1) * 8, "");
	printf ("%*s\033[1;36m22 23 24 25 26 27 28\033[m\n", (indent + 1) * 8, "");
	printf ("%*s\033[1;36m29 30 31            \033[m\n", (indent + 1) * 8, "");
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

	o->refcount       = 1;
	o->type           = MAGIC_MONTH;
	o->release        = (object_release_fn) month_release;
	m->folder.display = (folder_display_fn) month_display;

	return m;
}

int
month_add_child (MONTH *m, void *child)
{
	if (!m || !child) {
		return 0;
	}

	return 1;
}

