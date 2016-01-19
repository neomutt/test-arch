#include <stdio.h>
#include <stdlib.h>

#include "folder.h"
#include "item.h"

const int MAGIC_FOLDER = 1003;

static void
folder_free (FOLDER *f)
{
	if (!f) {
		return;
	}

	OBJECT *o = &f->object;
	o->refcount--;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < f->num_folders; i++) {
			// printf ("freeing folder %p\n", (void*) f->folders[i]);
			folder_free (f->folders[i]);
		}

		for (i = 0; i < f->num_items; i++) {
			// printf ("freeing item %p\n", (void*) f->items[i]);
			object_release (f->items[i]);
		}

		free (f->name);
		free (f);
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
	o->release  = (object_release_fn) folder_free;

	return f;
}

int
folder_add_folder (FOLDER *f, FOLDER *child)
{
	if (!f || !child) {
		return 0;
	}

	object_addref (child);
	f->folders[f->num_folders] = child;
	f->num_folders++;

	return 1;
}

int
folder_add_item (FOLDER *f, ITEM *i)
{
	if (!f || !i) {
		return 0;
	}

	object_addref (i);
	f->items[f->num_items] = i;
	f->num_items++;

	return 1;
}

void
folder_display (FOLDER *f, int indent)
{
	if (!f) {
		return;
	}

	printf ("%*s\033[1;32m%s\033[m\n", indent * 8, "", f->name);

	int i;

	for (i = 0; i < f->num_items; i++) {
		item_display (f->items[i], indent + 1);
	}

	for (i = 0; i < f->num_folders; i++) {
		folder_display (f->folders[i], indent + 1);
	}
}
