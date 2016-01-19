#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "folder.h"

const int MAGIC_SOURCE = 1002;

static void
source_free (SOURCE *src)
{
	if (!src) {
		return;
	}

	OBJECT *o = &src->object;
	o->refcount--;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < src->num_folders; i++) {
			// printf ("freeing folder %p\n", (void*) src->folders[i]);
			object_release (src->folders[i]);
		}

		free (src->name);
		free (src);
	}
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
	o->release  = (object_release_fn) source_free;

	return s;
}

int
source_add_folder (SOURCE *src, FOLDER *f)
{
	if (!src || !f) {
		return 0;
	}

	object_addref (f);
	src->folders[src->num_folders] = f;
	src->num_folders++;

	return 1;
}

void
source_display (SOURCE *src, int indent)
{
	if (!src) {
		return;
	}

	printf ("%*s\033[1;33m%s\033[m\n", indent * 8, "", src->name);

	int i;
	for (i = 0; i < src->num_folders; i++) {
		folder_display (src->folders[i], indent + 1);
	}
}
