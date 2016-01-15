#include <stdio.h>
#include <stdlib.h>

#include "source.h"
#include "folder.h"

void
source_free (SOURCE *src)
{
	if (!src) {
		return;
	}

	int i;
	for (i = 0; i < src->num_folders; i++) {
		// printf ("freeing folder %p\n", (void*) src->folders[i]);
		folder_free (src->folders[i]);
	}

	free (src->name);
	free (src);
}

int
source_add_folder (SOURCE *src, FOLDER *f)
{
	if (!src || !f) {
		return 0;
	}

	src->folders[src->num_folders] = f;
	src->num_folders++;

	return 1;
}

void
source_display (SOURCE *src)
{
	if (!src) {
		return;
	}

	printf ("\t%s\n", src->name);
	int i;
	for (i = 0; i < src->num_folders; i++) {
		folder_display (src->folders[i]);
	}
}
