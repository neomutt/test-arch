#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "nntp.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

void
nntp_release (NNTP_SOURCE *n)
{
	if (!n) {
		return;
	}

	// Nothing CALENDAR_SOURCE-specific to release

	source_release (&n->source);	// Release parent
}

NNTP_SOURCE *
nntp_create (NNTP_SOURCE *n)
{
	if (!n) {
		n = calloc (1, sizeof (NNTP_SOURCE));
		if (!n) {
			return NULL;
		}
	}

	source_create (&n->source);	// Construct parent

	OBJECT *o = &n->source.container.object;

	o->type     = MAGIC_NNTP;
	o->release  = (object_release_fn) nntp_release;

	return n;
}


static SOURCE *
nntp_init (void)
{
	NNTP_SOURCE *ns = nntp_create (NULL);
	if (!ns) {
		return NULL;
	}

	return &ns->source;
}

static int
nntp_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'a') && (name[0] <= 'e')) {
		// printf ("nntp config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
nntp_connect (SOURCE *s)
{
	s->container.object.type = MAGIC_NNTP;
	s->container.object.name = strdup ("nntp");

	// Pretend to read something

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);

	if (!f1 || !f2 || !f3) {
		printf ("nntp_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("alt.swedish.chef");
	f2->container.object.name = strdup ("rec.arts.poems");
	f3->container.object.name = strdup ("sci.fractals");

	EMAIL *e1 = email_create (NULL);
	EMAIL *e2 = email_create (NULL);
	EMAIL *e3 = email_create (NULL);
	EMAIL *e4 = email_create (NULL);
	EMAIL *e5 = email_create (NULL);
	EMAIL *e6 = email_create (NULL);
	EMAIL *e7 = email_create (NULL);

	if (!e1 || !e2 || !e3 || !e4 || !e5 || !e6 || !e7) {
		printf ("nntp_connect: email_create failed\n");
		return NULL;
	}

	e1->item.object.name = strdup ("bork");
	e2->item.object.name = strdup ("bork");
	e3->item.object.name = strdup ("bork");
	e4->item.object.name = strdup ("daffodils");
	e5->item.object.name = strdup ("elegy");
	e6->item.object.name = strdup ("mandelbrot");
	e7->item.object.name = strdup ("siepinski");

	folder_add_child (f1, e1);
	folder_add_child (f1, e2);
	folder_add_child (f1, e3);
	folder_add_child (f2, e4);
	folder_add_child (f2, e5);
	folder_add_child (f3, e6);
	folder_add_child (f3, e7);

	release (e1);
	release (e2);
	release (e3);
	release (e4);
	release (e5);
	release (e6);
	release (e7);

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);

	release (f1);
	release (f2);
	release (f3);
}

static void
nntp_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN nntp_plugin = {
	MAGIC_NNTP,
	"nntp",
	nntp_init,
	nntp_config_item,
	nntp_connect,
	nntp_disconnect
};

