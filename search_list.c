#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "plugin.h"
#include "search_list.h"
#include "source.h"
#include "view.h"

static void
check_email (ITEM *item, FOLDER *rcpt, int rule)
{
	if (!item || !rcpt) {
		return;
	}

	const char *name = item->object.name;
	// printf ("Check, %d %s\n", rule, name);

	int match = 0;
	int len;
	int i;

	switch (rule) {
		case 1:
			if (name[0] == 'b') {
				match = 1;
			}
			break;
		case 2:
			len = strlen (name);
			if (name[len - 1] == 'y') {
				match = 1;
			}
			break;
		case 3:
			len = strlen (name);
			for (i = 1; i < len; i++) {
				if (name[i - 1] == name[i]) {
					match = 1;
					break;
				}
			}
			break;
	}

	if (match) {
		folder_add_child (rcpt, item);
	}
}

static void
descend_folders (FOLDER *search, FOLDER *rcpt, int rule)
{
	if (!search || !rcpt) {
		return;
	}

	if (rule) {}

	int i;
	for (i = 0; search->folders[i]; i++) {
		// printf ("Folder: %s\n", search->folders[i]->object.name);
		descend_folders (search->folders[i], rcpt, rule);
	}

	for (i = 0; search->items[i]; i++) {
		ITEM *item = search->items[i];
		// printf ("Item: %s\n", item->object.name);
		check_email (item, rcpt, rule);
	}
}

static void
find_all_mail (SOURCE **sources, FOLDER *rcpt, int rule)
{
	if (!sources || !rcpt) {
		return;
	}

	if (rule) {}

	int s;
	for (s = 0; sources[s]; s++) {
		int f;
		for (f = 0; sources[s]->folders[f]; f++) {
			// printf ("Folder0: %s\n", sources[s]->folders[f]->object.name);
			descend_folders (sources[s]->folders[f], rcpt, rule);
		}

		int i;
		for (i = 0; sources[s]->items[i]; i++) {
			ITEM *item = sources[s]->items[i];
			// printf ("Item0: %s\n", item->object.name);
			check_email (item, rcpt, rule);
		}
	}
}


static int
search_list_release (SEARCH_LIST_SOURCE *s)
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

		for (i = 0; i < s->source.num_sources; i++) {
			object_release (s->source.sources[i]);
		}

		free (s->source.object.name);
		free (s);
	}

	return rc;
}

static SEARCH_LIST_SOURCE *
search_list_create (void)
{
	SEARCH_LIST_SOURCE *s = NULL;

	s = calloc (1, sizeof (SEARCH_LIST_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_SEARCH_LIST;
	o->release  = (object_release_fn) search_list_release;
	o->display  = (object_display_fn) source_display;

	return s;
}


static SOURCE *
search_list_init (void)
{
	SEARCH_LIST_SOURCE *is = search_list_create();
	if (!is) {
		return NULL;
	}

	return &is->source;
}

static int
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

static void
search_list_connect (SOURCE *s)
{
	s->object.type = MAGIC_SEARCH_LIST;
	s->object.name = strdup ("search_list");

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("search_list_connect: folder_create failed\n");
		return NULL;
	}

	f1->object.name = strdup ("^b");
	f2->object.name = strdup ("y$");
	f3->object.name = strdup ("(.){2}");

	find_all_mail (s->sources, f1, 1);
	find_all_mail (s->sources, f2, 2);
	find_all_mail (s->sources, f3, 3);

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);

	object_release (f1);
	object_release (f2);
	object_release (f3);
}

static void
search_list_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN search_list_plugin = {
	MAGIC_SEARCH_LIST,
	"search_list",
	search_list_init,
	search_list_config_item,
	search_list_connect,
	search_list_disconnect
};

