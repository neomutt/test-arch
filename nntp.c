#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "email.h"
#include "folder.h"
#include "nntp.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

static int
nntp_release (NNTP_SOURCE *s)
{
	if (!s) {
		return -1;
	}

	OBJECT *o = &s->source.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		int i;
		for (i = 0; i < s->source.num_folders; i++) {
			object_release (s->source.folders[i]);
		}

		for (i = 0; i < s->source.num_items; i++) {
			object_release (s->source.items[i]);
		}

		free (s->source.object.name);
		free (s);
	}

	return rc;
}

static NNTP_SOURCE *
nntp_create (void)
{
	NNTP_SOURCE *s = NULL;

	s = calloc (1, sizeof (NNTP_SOURCE));
	if (!s) {
		return NULL;
	}

	OBJECT *o = &s->source.object;

	o->refcount = 1;
	o->type     = MAGIC_NNTP;
	o->release  = (object_release_fn) nntp_release;
	o->display  = (object_display_fn) source_display;

	return s;
}


static SOURCE *
nntp_init (void)
{
	NNTP_SOURCE *ns = nntp_create();
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
	s->object.type = MAGIC_NNTP;
	s->object.name = strdup ("nntp");

	// Pretend to read something

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("nntp_connect: folder_create failed\n");
		return NULL;
	}

	f1->object.name = strdup ("alt.swedish.chef");
	f2->object.name = strdup ("rec.arts.poems");
	f3->object.name = strdup ("sci.fractals");

	EMAIL *e1 = email_create();
	EMAIL *e2 = email_create();
	EMAIL *e3 = email_create();
	EMAIL *e4 = email_create();
	EMAIL *e5 = email_create();
	EMAIL *e6 = email_create();
	EMAIL *e7 = email_create();

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

