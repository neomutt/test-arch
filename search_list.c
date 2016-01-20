#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "plugin.h"
#include "search_list.h"
#include "source.h"
#include "view.h"

static int
search_list_source_release (SEARCH_LIST_SOURCE *s)
{
	if (!s) {
		return -1;
	}

	OBJECT *o = &s->source.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < s->source.num_folders; i++) {
			object_release (s->source.folders[i]);
		}

		for (i = 0; i < s->source.num_items; i++) {
			object_release (s->source.items[i]);
		}

		free (s->source.name);
		free (s);
	}

	return rc;
}

SEARCH_LIST_SOURCE *
search_list_source_create (void)
{
	SEARCH_LIST_SOURCE *s = NULL;

	s = calloc (1, sizeof (SEARCH_LIST_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_SEARCH_LIST;
	o->release  = (object_release_fn) search_list_source_release;

	return s;
}

int
search_list_init (void)
{
	return 1;
}

SOURCE *
search_list_connect (void)
{
	SEARCH_LIST_SOURCE *is = NULL;

	is = search_list_source_create();
	if (!is) {
		return NULL;
	}

	SOURCE *s = &is->source;

	s->object.type = MAGIC_SEARCH_LIST;
	s->name        = strdup ("search_list");

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("search_list_connect: folder_create failed\n");
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
			printf ("search_list_connect: email_create failed\n");
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
search_list_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'e') && (name[0] <= 'h')) {
		// printf ("search_list config: %s\n", name);
		return 1;
	}

	return 0;
}

void
search_list_disconnect (void)
{
}

PLUGIN search_list_plugin = {
	MAGIC_SEARCH_LIST,
	"search_list",
	search_list_init,
	search_list_connect,
	search_list_disconnect,
	search_list_config_item
};


