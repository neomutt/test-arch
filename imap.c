#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "imap.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

// static char *config[10];

static void
imap_source_free (IMAP_SOURCE *s)
{
	if (!s) {
		return;
	}

	OBJECT *o = &s->source.object;
	o->refcount--;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < s->source.num_folders; i++) {
			// printf ("freeing folder %p\n", (void*) s->source.folders[i]);
			object_release (s->source.folders[i]);
		}

		for (i = 0; i < s->source.num_items; i++) {
			// printf ("freeing item %p\n", (void*) s->source.items[i]);
			object_release (s->source.items[i]);
		}

		free (s->source.name);
		free (s);
	}
}

IMAP_SOURCE *
imap_source_create (void)
{
	IMAP_SOURCE *s = NULL;

	s = calloc (1, sizeof (IMAP_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_IMAP;
	o->release  = (object_release_fn) imap_source_free;

	return s;
}

int
imap_init (void)
{
	// printf ("imap init\n");
	return 1;
}

SOURCE *
imap_connect (void)
{
	IMAP_SOURCE *is = NULL;

	is = imap_source_create();
	if (!is) {
		return NULL;
	}

	SOURCE *s = &is->source;

	s->object.type = MAGIC_IMAP;
	s->name        = strdup ("imap");

	// Pretend to read something

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("imap_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("fruit");
	f2->name = strdup ("cars");
	f3->name = strdup ("girls");

	const char *names[] = { "apple", "banana", "cherry", "audi", "bentley", "anna", "bella", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create();
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return NULL;
		}
		e->item.name = strdup (names[i]);

		if (i < 3) {
			folder_add_child (f1, e);
		} else if (i < 5) {
			folder_add_child (f2, e);
		} else {
			folder_add_child (f3, e);
		}
		object_release (e);
	}

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);

	object_release (f1);
	object_release (f2);
	object_release (f3);

	return s;
}

int
imap_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'a') && (name[0] <= 'e')) {
		// printf ("imap config: %s\n", name);
		return 1;
	}

	return 0;
}

void
imap_disconnect (void)
{
}

PLUGIN imap_plugin = {
	MAGIC_IMAP,
	"imap",
	imap_init,
	imap_connect,
	imap_disconnect,
	imap_config_item
};


