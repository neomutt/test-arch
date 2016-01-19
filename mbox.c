#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "mbox.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

// static char *config[10];

int
mbox_init (void)
{
	// printf ("mbox init\n");
	return 1;
}

SOURCE *
mbox_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_MBOX;
	s->name        = strdup ("mbox");

	// Pretend to read something

	FOLDER *f1 = folder_create();
	if (!f1) {
		printf ("mbox_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("music");

	EMAIL *e1 = email_create();
	EMAIL *e2 = email_create();
	EMAIL *e3 = email_create();
	EMAIL *e4 = email_create();

	if (!e1 || !e2 || !e3 || !e4) {
		printf ("mbox_connect: email_create failed\n");
		return NULL;
	}

	e1->item.name = strdup ("acdc");
	e2->item.name = strdup ("beatles");
	e3->item.name = strdup ("cream");
	e4->item.name = strdup ("doors");

	folder_add_child (f1, e1);
	folder_add_child (f1, e2);
	folder_add_child (f1, e3);
	folder_add_child (f1, e4);

	object_release (e1);
	object_release (e2);
	object_release (e3);
	object_release (e4);

	source_add_child (s, f1);

	object_release (f1);

	return s;
}

int
mbox_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'n') && (name[0] <= 'w')) {
		// printf ("mbox config: %s\n", name);
		return 1;
	}

	return 0;
}

void
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

