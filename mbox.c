#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "mbox.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

static int
mbox_release (MBOX_SOURCE *s)
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

		free (o->name);
		free (s);
	}

	return rc;
}

static MBOX_SOURCE *
mbox_create (void)
{
	MBOX_SOURCE *s = NULL;

	s = calloc (1, sizeof (MBOX_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_MBOX;
	o->release  = (object_release_fn) mbox_release;
	o->display  = (object_display_fn) source_display;

	return s;
}

static int
mbox_init (void)
{
	return 1;
}

static SOURCE *
mbox_connect (void)
{
	MBOX_SOURCE *ms = NULL;

	ms = mbox_create();
	if (!ms) {
		return NULL;
	}

	SOURCE *s = &ms->source;

	s->object.type = MAGIC_MBOX;
	s->object.name = strdup ("mbox");

	FOLDER *f1 = folder_create();
	if (!f1) {
		printf ("mbox_connect: folder_create failed\n");
		return NULL;
	}

	f1->object.name = strdup ("music");

	const char *names[] = { "acdc", "beatles", "cream", "doors", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create();
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return NULL;
		}
		e->item.object.name = strdup (names[i]);

		folder_add_child (f1, e);
		object_release (e);
	}

	source_add_child (s, f1);

	object_release (f1);

	return s;
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
mbox_disconnect (void)
{
}

PLUGIN mbox_plugin = {
	MAGIC_MBOX,
	"mbox",
	mbox_init,
	mbox_connect,
	mbox_disconnect,
	mbox_config_item
};

