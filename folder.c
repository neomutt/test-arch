#include <stdio.h>
#include <stdlib.h>

#include "folder.h"
#include "item.h"

void
folder_free (FOLDER *f)
{
	if (!f) {
		return;
	}

	int i;
	for (i = 0; i < f->num_items; i++) {
		// printf ("freeing item %p\n", (void*) f->items[i]);
		item_free (f->items[i]);
	}

	free (f->name);
	free (f);
}

int
folder_add_item (FOLDER *f, ITEM *i)
{
	if (!f || !i) {
		return 0;
	}

	f->items[f->num_items] = i;
	f->num_items++;

	return 1;
}

