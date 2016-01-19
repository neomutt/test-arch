#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "article.h"

static void
article_free (ARTICLE *a)
{
	if (!a) {
		return;
	}

	OBJECT *o = &a->item.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (a->item.name);
		free (a);
	}
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
	o->release  = (object_release_fn) article_free;

	return a;
}


