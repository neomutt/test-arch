#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "article.h"
#include "folder.h"
#include "item.h"
#include "plugin.h"
#include "rss.h"
#include "source.h"
#include "task.h"
#include "view.h"

void
rss_release (RSS *r)
{
	if (!r) {
		return;
	}

	// Nothing RSS-specific to release

	source_release (&r->source);	// Release parent
}

RSS *
rss_create (RSS *r)
{
	if (!r) {
		r = calloc (1, sizeof (RSS));
		if (!r) {
			return NULL;
		}
	}

	source_create (&r->source);	// Construct parent

	OBJECT *o = &r->source.container.object;

	o->type    = MAGIC_RSS;
	o->name    = strdup ("rss");
	o->release = (object_release_fn) rss_release;

	return r;
}


static SOURCE *
rss_init (void)
{
	RSS *rs = rss_create (NULL);
	if (!rs) {
		return NULL;
	}

	return &rs->source;
}

static int
rss_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'q') && (name[0] <= 't')) {
		// printf ("rss config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
rss_connect (SOURCE *s)
{
	RSS *rs = (RSS*) s;

	const char *feeds[] = { "slashdot.org", "arstechnica.co.uk", "bbc.co.uk", NULL };

	int i;

	for (i = 0; feeds[i]; i++) {
		rs->feeds[i] = folder_create (NULL);
		if (!rs->feeds[i]) {
			printf ("rss_connect: folder_create failed\n");
			return NULL;
		}
		rs->feeds[i]->container.object.name = strdup (feeds[i]);

		add_child (s, rs->feeds[i]);	// Source owns all feeds

		release (rs->feeds[i]);
	}

	rs->feeds[i] = NULL;

	const char *names[] = { "new battery tech", "privacy concerns", "faster processor", "electric vehicle", "eff defends", "old woman", "bad weather", NULL };

	for (i = 0; names[i]; i++) {
		ARTICLE *a = article_create (NULL);
		if (!a) {
			printf ("rss_connect: article_create failed\n");
			return NULL;
		}

		a->item.object.name = strdup (names[i]);

		if (i < 3) {
			add_child (rs->feeds[0], a);
		} else if (i < 5) {
			add_child (rs->feeds[1], a);
		} else {
			add_child (rs->feeds[2], a);
		}

		release (a);
	}

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);

	if (!f1 || !f2) {
		printf ("rss_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("tech");
	f2->container.object.name = strdup ("news");

	for (i = 0; rs->feeds[i]; i++) {
		if (i < 2) {
			add_child (f1, rs->feeds[i]);
		} else {
			add_child (f2, rs->feeds[i]);
		}
	}

	add_child (s, f1);
	add_child (s, f2);

	release (f1);
	release (f2);
}

static void
rss_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN rss_plugin = {
	MAGIC_TASK,
	"task",
	rss_init,
	rss_config_item,
	rss_connect,
	rss_disconnect
};

