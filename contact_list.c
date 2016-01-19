#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"
#include "contact_list.h"
#include "folder.h"
#include "item.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

// static char *config[10];

int
contact_list_init (void)
{
	// printf ("contact_list init\n");
	return 1;
}

SOURCE *
contact_list_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_CONTACT_LIST;
	s->name        = strdup ("contact list");

	// Pretend to read something

	const char *names[] = { "avon",   "bedford", "cornwall", "devon dog",         "essex echidna",     "ferrari", "gloucestershire goat", "horse",  "igloo", NULL   };
	const C_TAGS tags[] = { C_COUNTY, C_COUNTY,  C_COUNTY,   C_COUNTY | C_ANIMAL, C_COUNTY | C_ANIMAL, C_CAR,     C_COUNTY | C_ANIMAL,    C_ANIMAL, C_NONE,  C_NONE };
	CONTACT *contacts[10];

	int i;

	for (i = 0; names[i]; i++) {
		contacts[i] = contact_create();
		if (!contacts[i]) {
			printf ("contact_list_connect: item_create failed\n");
			return NULL;
		}
		contacts[i]->item.name = strdup (names[i]);
		contacts[i]->tags      = tags[i];

		source_add_child (s, contacts[i]);	// Source owns all items
	}

	contacts[i] = NULL;

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();
	FOLDER *f4 = folder_create();

	if (!f1 || !f2 || !f3 || !f4) {
		printf ("contact_list_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("county");
	f2->name = strdup ("animal");
	f3->name = strdup ("county + animal");
	f4->name = strdup ("untagged");

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags & C_COUNTY) {
			folder_add_child (f1, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags & C_ANIMAL) {
			folder_add_child (f2, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if ((contacts[i]->tags & C_COUNTY) && (contacts[i]->tags & C_ANIMAL)) {
			folder_add_child (f3, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags == C_NONE) {
			folder_add_child (f4, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		object_release (contacts[i]);
	}

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);
	source_add_child (s, f4);

	object_release (f1);
	object_release (f2);
	object_release (f3);
	object_release (f4);

	return s;
}

int
contact_list_config_item (const char *name)
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
contact_list_disconnect (void)
{
}

PLUGIN contact_list_plugin = {
	MAGIC_CONTACT,
	"contact",
	contact_list_init,
	contact_list_connect,
	contact_list_disconnect,
	contact_list_config_item
};

