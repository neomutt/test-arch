#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "folder.h"
#include "item.h"
#include "maildir.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

// static char *config[10];

int
maildir_init (void)
{
	// printf ("maildir init\n");
	return 1;
}

SOURCE *
maildir_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_MAILDIR;
	s->name        = strdup ("maildir");

	// Pretend to read something

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("maildir_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("boys");
	f2->name = strdup ("trees");
	f3->name = strdup ("fish");

	folder_add_child (f1, f2);
	folder_add_child (f1, f3);

	object_release (f2);
	object_release (f3);

	ITEM *i1 = item_create();
	ITEM *i2 = item_create();
	ITEM *i3 = item_create();
	ITEM *i4 = item_create();
	ITEM *i5 = item_create();
	ITEM *i6 = item_create();
	ITEM *i7 = item_create();

	if (!i1 || !i2 || !i3 || !i4 || !i5 || !i6 || !i7) {
		printf ("maildir_connect: item_create failed\n");
		return NULL;
	}

	i1->name = strdup ("adam");
	i2->name = strdup ("barry");
	i3->name = strdup ("charlie");
	i4->name = strdup ("ash");
	i5->name = strdup ("beech");
	i6->name = strdup ("angel");
	i7->name = strdup ("beluga");

	folder_add_child (f1, i1);
	folder_add_child (f1, i2);
	folder_add_child (f1, i3);
	folder_add_child (f2, i4);
	folder_add_child (f2, i5);
	folder_add_child (f3, i6);
	folder_add_child (f3, i7);

	object_release (i1);
	object_release (i2);
	object_release (i3);
	object_release (i4);
	object_release (i5);
	object_release (i6);
	object_release (i7);

	source_add_child (s, f1);

	object_release (f1);

	return s;
}

int
maildir_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'f') && (name[0] <= 'm')) {
		// printf ("maildir config: %s\n", name);
		return 1;
	}

	return 0;
}

void
maildir_disconnect (void)
{
}

PLUGIN maildir_plugin = {
	MAGIC_MAILDIR,
	"maildir",
	maildir_init,
	maildir_connect,
	maildir_disconnect,
	maildir_config_item
};

