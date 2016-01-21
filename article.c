#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "article.h"

void
article_release (ARTICLE *a)
{
	if (!a) {
		return;
	}

	// Nothing ARTICLE-specific to release

	item_release (&a->item);	// Release parent
}

ARTICLE *
article_create (ARTICLE *a)
{
	if (!a) {
		a = calloc (1, sizeof (ARTICLE));
		if (!a) {
			return NULL;
		}
	}

	item_create (&a->item);	// Construct parent

	OBJECT *o = &a->item.object;

	o->type     = MAGIC_ARTICLE;
	o->release  = (object_release_fn) article_release;

	return a;
}

