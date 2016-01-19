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

int
imap_init (void)
{
	// printf ("imap init\n");
	return 1;
}

SOURCE *
imap_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

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

	EMAIL *e1 = email_create();
	EMAIL *e2 = email_create();
	EMAIL *e3 = email_create();
	EMAIL *e4 = email_create();
	EMAIL *e5 = email_create();
	EMAIL *e6 = email_create();
	EMAIL *e7 = email_create();

	if (!e1 || !e2 || !e3 || !e4 || !e5 || !e6 || !e7) {
		printf ("imap_connect: email_create failed\n");
		return NULL;
	}

	e1->item.name = strdup ("apple");
	e2->item.name = strdup ("banana");
	e3->item.name = strdup ("cherry");
	e4->item.name = strdup ("audi");
	e5->item.name = strdup ("bentley");
	e6->item.name = strdup ("anna");
	e7->item.name = strdup ("bella");

	folder_add_child (f1, e1);
	folder_add_child (f1, e2);
	folder_add_child (f1, e3);
	folder_add_child (f2, e4);
	folder_add_child (f2, e5);
	folder_add_child (f3, e6);
	folder_add_child (f3, e7);

	object_release (e1);
	object_release (e2);
	object_release (e3);
	object_release (e4);
	object_release (e5);
	object_release (e6);
	object_release (e7);

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


