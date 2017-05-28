/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

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
mbox_destroy (MBOX *m)
{
	if (!m) {
		return;
	}

	// Nothing MBOX-specific to release

	source_destroy (&m->source);	// Destroy parent
}

MBOX *
mbox_create (MBOX *m)
{
	if (!m) {
		m = calloc (1, sizeof (MBOX));
		if (!m) {
			return NULL;
		}
	}

	source_create (&m->source);	// Construct parent

	OBJECT *o = &m->source.container.object;

	o->type    = MAGIC_MBOX;
	o->name    = strdup ("mbox");
	o->destroy = (object_destroy_fn) mbox_destroy;

	return m;
}


static SOURCE *
mbox_init (void)
{
	MBOX *ms = mbox_create (NULL);
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
	FOLDER *f1 = folder_create (NULL);
	if (!f1) {
		printf ("mbox_connect: folder_create failed\n");
		return;
	}

	f1->container.object.name = strdup ("music");

	const char *names[] = { "acdc", "beatles", "cream", "doors", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create (NULL);
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return;
		}
		e->item.object.name = strdup (names[i]);

		add_child (f1, e);
		release (e);
	}

	add_child (s, f1);

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

