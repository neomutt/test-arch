#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"
#include "folder.h"
#include "item.h"
#include "plugin.h"

#define MAGIC_CONTACT 456

// static char *config[10];

enum {
	C_GROUP,
	C_TAG
} contact_view;

int
contact_init (void)
{
	// printf ("contact init\n");
	return 1;
}

SOURCE *
contact_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_CONTACT;
	s->name        = strdup ("contact");

	// Pretend to read something

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();

	if (!f1 || !f2) {
		printf ("contact_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("county");
	f2->name = strdup ("animal");

	ITEM *i1 = item_create();
	ITEM *i2 = item_create();
	ITEM *i3 = item_create();
	ITEM *i4 = item_create();
	ITEM *i5 = item_create();
	ITEM *i6 = item_create();
	ITEM *i7 = item_create();
	ITEM *i8 = item_create();
	ITEM *i9 = item_create();

	if (!i1 || !i2 || !i3 || !i4 || !i5 || !i6 || !i7 || !i8 || !i9) {
		printf ("contact_connect: item_create failed\n");
		return NULL;
	}

	i1->name = strdup ("avon");
	i2->name = strdup ("bedford");
	i3->name = strdup ("cornwall");
	i4->name = strdup ("devon dog");
	i5->name = strdup ("essex echidna");
	i6->name = strdup ("frog");
	i7->name = strdup ("gloucestershire goat");
	i8->name = strdup ("horse");
	i9->name = strdup ("impala");

	i4->object.refcount++;
	i5->object.refcount++;
	i7->object.refcount++;

	folder_add_item (f1, i1);	// counties
	folder_add_item (f1, i2);
	folder_add_item (f1, i3);
	folder_add_item (f1, i4);
	folder_add_item (f1, i5);
	folder_add_item (f1, i7);

	folder_add_item (f2, i4);	// animals
	folder_add_item (f2, i5);
	folder_add_item (f2, i6);
	folder_add_item (f2, i7);
	folder_add_item (f2, i8);
	folder_add_item (f2, i9);

	source_add_folder (s, f1);
	source_add_folder (s, f2);

	return s;
}

int
contact_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'n') && (name[0] <= 'w')) {
		// printf ("contact config: %s\n", name);
		return 1;
	}

	return 0;
}

void
contact_disconnect (void)
{
}

PLUGIN contact_plugin = {
	MAGIC_CONTACT,
	"contact",
	contact_init,
	contact_connect,
	contact_disconnect,
	contact_config_item
};

