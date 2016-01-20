#include <stdio.h>
#include <stdlib.h>

#include "folder.h"
#include "source.h"

static int
source_release (SOURCE *src)
{
	if (!src) {
		return -1;
	}

	OBJECT *o = &src->object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < src->num_folders; i++) {
			// printf ("freeing folder %p\n", (void*) src->folders[i]);
			object_release (src->folders[i]);
		}

		for (i = 0; i < src->num_items; i++) {
			// printf ("freeing item %p\n", (void*) src->items[i]);
			object_release (src->items[i]);
		}

		free (src->name);
		free (src);
	}

	return rc;
}

SOURCE *
source_create (void)
{
	SOURCE *s = NULL;

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->object;
	o->refcount = 1;
	o->type     = MAGIC_SOURCE;
	o->release  = (object_release_fn) source_release;

	return s;
}

int
source_add_child (SOURCE *src, void *child)
{
	if (!src || !child) {
		return 0;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xff) == MAGIC_FOLDER) {
		object_addref (child);
		src->folders[src->num_folders] = child;
		src->num_folders++;
	} else if ((obj->type & 0xff) == MAGIC_ITEM) {
		object_addref (child);
		src->items[src->num_items] = child;
		src->num_items++;
	} else {
		printf ("can't add object:0x%04x to a source\n", obj->type);
		return 0;
	}

	return 1;
}

void
source_display (SOURCE *src, int indent)
{
	if (!src) {
		return;
	}

	printf ("%*s\033[1;33m%s\033[m\n", indent * 8, "", src->name);

	if (src->num_folders == 0) {
		printf ("%*s\033[1;32m[empty]\033[m\n", (indent + 1) * 8, "");
	} else {
		int i;

		for (i = 0; i < src->num_items; i++) {
			ITEM *it = src->items[i];
			it->display (it, indent + 1);
		}

		for (i = 0; i < src->num_folders; i++) {
			FOLDER *f = src->folders[i];
			f->display (f, indent + 1);
		}
	}
}
