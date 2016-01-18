#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "folder.h"

SOURCE *
source_create (void)
{
	SOURCE *s = NULL;

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->object;
	o->refcount    = 1;
	s->object.type = 1002;

	return s;
}

void
source_free (SOURCE *src)
{
	if (!src) {
		return;
	}

	int i;
	for (i = 0; i < src->num_folders; i++) {
		// printf ("freeing folder %p\n", (void*) src->folders[i]);
		folder_free (src->folders[i]);
	}

	OBJECT *o = &src->object;
	if (o->delete) {
		(*o->delete)();
	} else {
		o->refcount--;
		if (o->refcount < 1) {
			free (src->name);
			free (src);
		}
	}
}

int
source_add_folder (SOURCE *src, FOLDER *f)
{
	if (!src || !f) {
		return 0;
	}

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
