/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

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

void
contact_list_destroy (CONTACT_LIST *c)
{
	if (!c) {
		return;
	}

	// Nothing CONTACT_LIST-specific to release

	source_destroy (&c->source);	// Destroy parent
}

CONTACT_LIST *
contact_list_create (CONTACT_LIST *c)
{
	if (!c) {
		c = calloc (1, sizeof (CONTACT_LIST));
		if (!c) {
			return NULL;
		}
	}

	source_create (&c->source);	// Construct parent

	OBJECT *o = &c->source.container.object;

	o->type    = MAGIC_CONTACT_LIST;
	o->name    = strdup ("contact list");
	o->destroy = (object_destroy_fn) contact_list_destroy;

	return c;
}


static SOURCE *
contact_list_init (void)
{
	CONTACT_LIST *cs = contact_list_create (NULL);
	if (!cs) {
		return NULL;
	}

	return &cs->source;
}

static int
contact_list_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'a') && (name[0] <= 'd')) {
		// printf ("contact config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
contact_list_connect (SOURCE *s)
{
	const char *names[] = { "avon",   "bedford", "cornwall", "devon dog",         "essex echidna",     "ferrari", "gloucestershire goat", "horse",  "igloo", NULL   };
	const C_TAGS tags[] = { C_COUNTY, C_COUNTY,  C_COUNTY,   C_COUNTY | C_ANIMAL, C_COUNTY | C_ANIMAL, C_CAR,     C_COUNTY | C_ANIMAL,    C_ANIMAL, C_NONE,  C_NONE };
	CONTACT *contacts[10];

	int i;

	for (i = 0; names[i]; i++) {
		contacts[i] = contact_create (NULL);
		if (!contacts[i]) {
			printf ("contact_list_connect: contact_create failed\n");
			return;
		}
		contacts[i]->item.object.name = strdup (names[i]);
		contacts[i]->tags             = tags[i];

		add_child (s, contacts[i]);	// Source owns all contacts
	}

	contacts[i] = NULL;

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);
	FOLDER *f4 = folder_create (NULL);

	if (!f1 || !f2 || !f3 || !f4) {
		printf ("contact_list_connect: folder_create failed\n");
		return;
	}

	f1->container.object.name = strdup ("county");
	f2->container.object.name = strdup ("animal");
	f3->container.object.name = strdup ("county + animal");
	f4->container.object.name = strdup ("untagged");

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags & C_COUNTY) {
			add_child (f1, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags & C_ANIMAL) {
			add_child (f2, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if ((contacts[i]->tags & C_COUNTY) && (contacts[i]->tags & C_ANIMAL)) {
			add_child (f3, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		if (contacts[i]->tags == C_NONE) {
			add_child (f4, contacts[i]);
		}
	}

	for (i = 0; contacts[i]; i++) {
		release (contacts[i]);
	}

	add_child (s, f1);
	add_child (s, f2);
	add_child (s, f3);
	add_child (s, f4);

	release (f1);
	release (f2);
	release (f3);
	release (f4);
}

static void
contact_list_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN contact_list_plugin = {
	MAGIC_CONTACT,
	"contact",
	contact_list_init,
	contact_list_config_item,
	contact_list_connect,
	contact_list_disconnect
};

