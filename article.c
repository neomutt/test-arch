/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "article.h"

void
article_destroy (ARTICLE *a)
{
	if (!a) {
		return;
	}

	// Nothing ARTICLE-specific to release

	item_destroy (&a->item);	// Destroy parent
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
	o->destroy  = (object_destroy_fn) article_destroy;

	return a;
}

