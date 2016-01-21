#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "maildir.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

static int
maildir_release (MAILDIR_SOURCE *s)
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

static MAILDIR_SOURCE *
maildir_create (void)
{
	MAILDIR_SOURCE *s = NULL;

	s = calloc (1, sizeof (MAILDIR_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_MAILDIR;
	o->release  = (object_release_fn) maildir_release;
	o->display  = (object_display_fn) source_display;

	return s;
}


static SOURCE *
maildir_init (void)
{
	MAILDIR_SOURCE *ms = maildir_create();
	if (!ms) {
		return NULL;
	}

	return &ms->source;
}

static int
maildir_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'i') && (name[0] <= 'l')) {
		// printf ("maildir config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
maildir_connect (SOURCE *s)
{
	s->object.type = MAGIC_MAILDIR;
	s->object.name = strdup ("maildir");

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("maildir_connect: folder_create failed\n");
		return NULL;
	}

	f1->object.name = strdup ("boys");
	f2->object.name = strdup ("trees");
	f3->object.name = strdup ("fish");

	const char *names[] = { "adam", "barry", "charlie", "ash", "beech", "angel", "beluga", NULL };

	int i;
	EMAIL *e;

	for (i = 0; names[i]; i++) {
		e = email_create();
		if (!e) {
			printf ("imap_connect: email_create failed\n");
			return NULL;
		}
		e->item.object.name = strdup (names[i]);

		if (i < 3) {
			folder_add_child (f1, e);
		} else if (i < 5) {
			folder_add_child (f2, e);
		} else {
			folder_add_child (f3, e);
		}
		object_release (e);
	}

	folder_add_child (f1, f2);
	folder_add_child (f1, f3);

	object_release (f2);
	object_release (f3);

	source_add_child (s, f1);

	object_release (f1);
}

static void
maildir_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN maildir_plugin = {
	MAGIC_MAILDIR,
	"maildir",
	maildir_init,
	maildir_config_item,
	maildir_connect,
	maildir_disconnect
};

