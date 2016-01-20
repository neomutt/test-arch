#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "article.h"

static int
article_release (ARTICLE *a)
{
	if (!a) {
		return -1;
	}

	OBJECT *o = &a->item.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (a->item.name);
		free (a);
	}

	return rc;
}

ARTICLE *
article_create (void)
{
	ARTICLE *a = NULL;

	a = calloc (1, sizeof (ARTICLE));
	if (!a) {
		return NULL;
	}

	OBJECT *o = &a->item.object;

	o->refcount = 1;
	o->type     = MAGIC_ARTICLE;
	o->release  = (object_release_fn) article_release;
	o->display  = (object_display_fn) item_display;

	return a;
}


