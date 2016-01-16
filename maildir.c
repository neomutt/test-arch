#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"
#include "folder.h"
#include "item.h"

#include "plugin.h"

#define MAGIC_MAILDIR 345

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

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	s->type = MAGIC_MAILDIR;
	s->name = strdup ("maildir");

	// Pretend to read something

	FOLDER *f1 = calloc (1, sizeof (FOLDER));
	FOLDER *f2 = calloc (1, sizeof (FOLDER));
	FOLDER *f3 = calloc (1, sizeof (FOLDER));

	if (!f1 || !f2 || !f3) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	f1->name = strdup ("boys");
	f2->name = strdup ("trees");
	f3->name = strdup ("fish");

	folder_add_folder (f1, f2);
	folder_add_folder (f1, f3);

	ITEM *i1 = calloc (1, sizeof (ITEM));
	ITEM *i2 = calloc (1, sizeof (ITEM));
	ITEM *i3 = calloc (1, sizeof (ITEM));
	ITEM *i4 = calloc (1, sizeof (ITEM));
	ITEM *i5 = calloc (1, sizeof (ITEM));
	ITEM *i6 = calloc (1, sizeof (ITEM));
	ITEM *i7 = calloc (1, sizeof (ITEM));

	if (!i1 || !i2 || !i3 || !i4 || !i5 || !i6 || !i7) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	i1->name = strdup ("adam");
	i2->name = strdup ("barry");
	i3->name = strdup ("charlie");
	i4->name = strdup ("ash");
	i5->name = strdup ("beech");
	i6->name = strdup ("angel");
	i7->name = strdup ("beluga");

	folder_add_item (f1, i1);
	folder_add_item (f1, i2);
	folder_add_item (f1, i3);
	folder_add_item (f2, i4);
	folder_add_item (f2, i5);
	folder_add_item (f3, i6);
	folder_add_item (f3, i7);

	source_add_folder (s, f1);

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

static PLUGIN p = {
	MAGIC_MAILDIR,
	"maildir",
	maildir_init,
	maildir_connect,
	maildir_disconnect,
	maildir_config_item
};

PLUGIN *maildir_plugin = &p;

