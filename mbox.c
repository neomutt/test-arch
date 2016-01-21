#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "mbox.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

void
mbox_release (MBOX_SOURCE *m)
{
	if (!m) {
		return;
	}

	// Nothing MBOX_SOURCE-specific to release

	source_release (&m->source);	// Release parent
}

MBOX_SOURCE *
mbox_create (MBOX_SOURCE *m)
{
	if (!m) {
		m = calloc (1, sizeof (MBOX_SOURCE));
		if (!m) {
			return NULL;
		}
	}

	source_create (&m->source);	// Construct parent

	OBJECT *o = &m->source.container.object;

	o->type     = MAGIC_MBOX;
	o->release  = (object_release_fn) mbox_release;

	return m;
}


static SOURCE *
mbox_init (void)
{
	MBOX_SOURCE *ms = mbox_create (NULL);
	if (!ms) {
		return NULL;
	}

	return &ms->source;
}

static int
mbox_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'm') && (name[0] <= 'p')) {
		// printf ("mbox config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
mbox_connect (SOURCE *s)
{
	s->container.object.type = MAGIC_MBOX;
	s->container.object.name = strdup ("mbox");

	FOLDER *f1 = folder_create (NULL);
	if (!f1) {
		printf ("mbox_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("music");

	const char *names[] = { "acdc", "beatles", "cream", "doors", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create (NULL);
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return NULL;
		}
		e->item.object.name = strdup (names[i]);

		folder_add_child (f1, e);
		release (e);
	}

	source_add_child (s, f1);

	release (f1);
}

static void
mbox_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN mbox_plugin = {
	MAGIC_MBOX,
	"mbox",
	mbox_init,
	mbox_config_item,
	mbox_connect,
	mbox_disconnect
};

