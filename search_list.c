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
	for (i = 0; search->container.children[i]; i++) {
		// printf ("Folder: %s\n", search->folders[i]->object.name);
		descend_folders ((FOLDER*) search->container.children[i], rcpt, rule);
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
		for (f = 0; sources[s]->container.children[f]; f++) {
			// printf ("Folder0: %s\n", sources[s]->folders[f]->object.name);
			descend_folders ((FOLDER*) sources[s]->container.children[f], rcpt, rule);
		}

		int i;
		for (i = 0; sources[s]->items[i]; i++) {
			ITEM *item = sources[s]->items[i];
			// printf ("Item0: %s\n", item->object.name);
			check_email (item, rcpt, rule);
		}
	}
}


void
search_list_release (SEARCH_LIST_SOURCE *s)
{
	if (!s) {
		return;
	}

	int i;
	for (i = 0; s->sources[i]; i++) {
		release (s->sources[i]);
	}

	source_release (&s->source);	// Release parent
}

int
search_list_add_child (SEARCH_LIST_SOURCE *s, void *child)
{
	if (!s || !child) {
		return -1;
	}

	OBJECT *obj = child;
	if ((obj->type & 0xff) == MAGIC_SOURCE) {
		object_addref (child);
		s->sources[s->num_sources] = child;
		s->num_sources++;
	} else {
		source_add_child (&s->source, child);
	}

	return 0;
}

SEARCH_LIST_SOURCE *
search_list_create (SEARCH_LIST_SOURCE *s)
{
	if (!s) {
		s = calloc (1, sizeof (SEARCH_LIST_SOURCE));
		if (!s) {
			return NULL;
		}
	}

	source_create (&s->source);	// Construct parent

	OBJECT *o = &s->source.container.object;

	o->type     = MAGIC_SEARCH_LIST;
	o->release  = (object_release_fn) search_list_release;

	CONTAINER *c = &s->source.container;

	c->add_child = (container_add_child_fn) search_list_add_child;

	return s;
}


static SOURCE *
search_list_init (void)
{
	SEARCH_LIST_SOURCE *is = search_list_create (NULL);
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
	s->container.object.type = MAGIC_SEARCH_LIST;
	s->container.object.name = strdup ("search_list");

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);

	if (!f1 || !f2 || !f3) {
		printf ("search_list_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("^b");
	f2->container.object.name = strdup ("y$");
	f3->container.object.name = strdup ("(.){2}");

	SEARCH_LIST_SOURCE *sl = (SEARCH_LIST_SOURCE*) s;

	find_all_mail (sl->sources, f1, 1);
	find_all_mail (sl->sources, f2, 2);
	find_all_mail (sl->sources, f3, 3);

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);

	release (f1);
	release (f2);
	release (f3);
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

