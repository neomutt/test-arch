#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "month.h"
#include "plugin.h"
#include "folder.h"
#include "view.h"

static void
month_folder_free (MONTH_FOLDER *f)
{
	if (!f) {
		return;
	}

	OBJECT *o = &f->folder.object;
	o->refcount--;
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
}

MONTH_FOLDER *
month_folder_create (void)
{
	MONTH_FOLDER *f = NULL;

	f = calloc (1, sizeof (MONTH_FOLDER));
	if (!f) {
		return NULL;
	}

	OBJECT *o = &f->folder.object;

	o->refcount = 1;
	o->type     = MAGIC_MONTH;
	o->release  = (object_release_fn) month_folder_free;

	return f;
}

void
month_display (FOLDER *f, int indent)
{
	printf ("1 2 3 4 5 6 7\n");
}

