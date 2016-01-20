#include <stdio.h>
#include <stdlib.h>

#include "folder.h"
#include "item.h"

static int
folder_release (FOLDER *f)
{
	if (!f) {
		return -1;
	}

	OBJECT *o = &f->object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < f->num_folders; i++) {
			// printf ("freeing folder %p\n", (void*) f->folders[i]);
			folder_release (f->folders[i]);
		}

		for (i = 0; i < f->num_items; i++) {
			// printf ("freeing item %p\n", (void*) f->items[i]);
			object_release (f->items[i]);
		}

		free (f->name);
		free (f);
	}

	return rc;
}

static void
folder_display (FOLDER *f, int indent)
{
	if (!f) {
		return;
	}

	printf ("%*s\033[1;32m%s\033[m\n", indent * 8, "", f->name);

	if ((f->num_items == 0) && (f->num_folders == 0)) {
		printf ("%*s\033[1;36m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		int i;

		for (i = 0; i < f->num_items; i++) {
			OBJECT *o = &f->items[i]->object;
			o->display (o, indent + 1);
		}

		for (i = 0; i < f->num_folders; i++) {
			folder_display (f->folders[i], indent + 1);
		}
	}
}

FOLDER *
folder_create (void)
{
	FOLDER *f = NULL;

	f = calloc (1, sizeof (FOLDER));
	if (!f) {
		return NULL;
	}

	OBJECT *o = &f->object;

	o->refcount = 1;
	o->type     = MAGIC_FOLDER;
	o->release  = (object_release_fn) folder_release;
	o->display  = (object_display_fn) folder_display;

	return f;
}

int
folder_add_child (FOLDER *f, void *child)
{
	if (!f || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xff) == MAGIC_FOLDER) {
		object_addref (child);
		f->folders[f->num_folders] = child;
		f->num_folders++;
	} else if ((obj->type & 0xff) == MAGIC_ITEM) {
		object_addref (child);
		f->items[f->num_items] = child;
		f->num_items++;
	} else {
		printf ("can't add object:0x%04x to a folder\n", obj->type);
		return 0;
	}

	return 1;
}

