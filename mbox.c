#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"
#include "folder.h"
#include "item.h"
#include "plugin.h"

#define MAGIC_MBOX 234

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

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_MBOX;
	s->name        = strdup ("mbox");

	// Pretend to read something

	FOLDER *f1 = calloc (1, sizeof (FOLDER));

	if (!f1) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	f1->name = strdup ("music");

	ITEM *i1 = calloc (1, sizeof (ITEM));
	ITEM *i2 = calloc (1, sizeof (ITEM));
	ITEM *i3 = calloc (1, sizeof (ITEM));
	ITEM *i4 = calloc (1, sizeof (ITEM));

	if (!i1 || !i2 || !i3 || !i4) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	i1->name = strdup ("acdc");
	i2->name = strdup ("beatles");
	i3->name = strdup ("cream");
	i4->name = strdup ("doors");

	folder_add_item (f1, i1);
	folder_add_item (f1, i2);
	folder_add_item (f1, i3);
	folder_add_item (f1, i4);

	source_add_folder (s, f1);

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

