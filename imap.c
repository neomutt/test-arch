#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "imap.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

void
imap_release (IMAP *i)
{
	if (!i) {
		return;
	}

	// Nothing IMAP-specific to release

	source_release (&i->source);	// Release parent
}

IMAP *
imap_create (IMAP *i)
{
	if (!i) {
		i = calloc (1, sizeof (IMAP));
		if (!i) {
			return NULL;
		}
	}

	source_create (&i->source);	// Construct parent

	OBJECT *o = &i->source.container.object;

	o->type     = MAGIC_IMAP;
	o->release  = (object_release_fn) imap_release;

	return i;
}


static SOURCE *
imap_init (void)
{
	IMAP *is = imap_create (NULL);
	if (!is) {
		return NULL;
	}

	return &is->source;
}

static int
imap_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'e') && (name[0] <= 'h')) {
		// printf ("imap config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
imap_connect (SOURCE *s)
{
	s->container.object.type = MAGIC_IMAP;
	s->container.object.name = strdup ("imap");

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);

	if (!f1 || !f2 || !f3) {
		printf ("imap_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("fruit");
	f2->container.object.name = strdup ("cars");
	f3->container.object.name = strdup ("girls");

	const char *names[] = { "apple", "banana", "cherry", "audi", "bentley", "anna", "bella", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create (NULL);
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return NULL;
		}
		e->item.object.name = strdup (names[i]);

		if (i < 3) {
			add_child (f1, e);
		} else if (i < 5) {
			add_child (f2, e);
		} else {
			add_child (f3, e);
		}
		release (e);
	}

	add_child (s, f1);
	add_child (s, f2);
	add_child (s, f3);

	release (f1);
	release (f2);
	release (f3);
}

static void
imap_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN imap_plugin = {
	MAGIC_IMAP,
	"imap",
	imap_init,
	imap_config_item,
	imap_connect,
	imap_disconnect
};

