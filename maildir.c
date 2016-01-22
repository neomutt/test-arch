#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "maildir.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

void
maildir_destroy (MAILDIR *m)
{
	if (!m) {
		return;
	}

	// Nothing MAILDIR-specific to release

	source_destroy (&m->source);	// Destroy parent
}

MAILDIR *
maildir_create (MAILDIR *m)
{
	if (!m) {
		m = calloc (1, sizeof (MAILDIR));
		if (!m) {
			return NULL;
		}
	}

	source_create (&m->source);	// Construct parent

	OBJECT *o = &m->source.container.object;

	o->type    = MAGIC_MAILDIR;
	o->name    = strdup ("maildir");
	o->destroy = (object_destroy_fn) maildir_destroy;

	return m;
}


static SOURCE *
maildir_init (void)
{
	MAILDIR *ms = maildir_create (NULL);
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
	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);

	if (!f1 || !f2 || !f3) {
		printf ("maildir_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("boys");
	f2->container.object.name = strdup ("trees");
	f3->container.object.name = strdup ("fish");

	const char *names[] = { "adam", "barry", "charlie", "ash", "beech", "angel", "beluga", NULL };

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

	add_child (f1, f2);
	add_child (f1, f3);

	release (f2);
	release (f3);

	add_child (s, f1);

	release (f1);
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

