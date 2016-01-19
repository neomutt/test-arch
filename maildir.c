#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
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

	EMAIL *e1 = email_create();
	EMAIL *e2 = email_create();
	EMAIL *e3 = email_create();
	EMAIL *e4 = email_create();
	EMAIL *e5 = email_create();
	EMAIL *e6 = email_create();
	EMAIL *e7 = email_create();

	if (!e1 || !e2 || !e3 || !e4 || !e5 || !e6 || !e7) {
		printf ("maildir_connect: item_create failed\n");
		return NULL;
	}

	e1->item.name = strdup ("adam");
	e2->item.name = strdup ("barry");
	e3->item.name = strdup ("charlie");
	e4->item.name = strdup ("ash");
	e5->item.name = strdup ("beech");
	e6->item.name = strdup ("angel");
	e7->item.name = strdup ("beluga");

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

