#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"
#include "folder.h"
#include "item.h"

const int MAGIC_MAILDIR = 345;

int
maildir_init (void)
{
	// printf ("maildir init\n");
	return 1;
}

SOURCE *
maildir_connect (void)
{
	SOURCE *s = NULL;

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	s->type = MAGIC_MAILDIR;
	s->name = strdup ("maildir");

	// Pretend to read something

	FOLDER *f1 = calloc (1, sizeof (FOLDER));
	FOLDER *f2 = calloc (1, sizeof (FOLDER));
	FOLDER *f3 = calloc (1, sizeof (FOLDER));

	if (!f1 || !f2 || !f3) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	f1->name = strdup ("fruit");
	f2->name = strdup ("cars");
	f3->name = strdup ("girls");

	folder_add_folder (f1, f2);
	folder_add_folder (f1, f3);

	ITEM *i1 = calloc (1, sizeof (ITEM));
	ITEM *i2 = calloc (1, sizeof (ITEM));
	ITEM *i3 = calloc (1, sizeof (ITEM));
	ITEM *i4 = calloc (1, sizeof (ITEM));
	ITEM *i5 = calloc (1, sizeof (ITEM));
	ITEM *i6 = calloc (1, sizeof (ITEM));
	ITEM *i7 = calloc (1, sizeof (ITEM));

	if (!i1 || !i2 || !i3 || !i4 || !i5 || !i6 || !i7) {
		printf ("imap_connect: calloc failed\n");
		return NULL;
	}

	i1->name = strdup ("apple");
	i2->name = strdup ("banana");
	i3->name = strdup ("cherry");
	i4->name = strdup ("audi");
	i5->name = strdup ("bentley");
	i6->name = strdup ("anna");
	i7->name = strdup ("bella");

	folder_add_item (f1, i1);
	folder_add_item (f1, i2);
	folder_add_item (f1, i3);
	folder_add_item (f2, i4);
	folder_add_item (f2, i5);
	folder_add_item (f3, i6);
	folder_add_item (f3, i7);

	source_add_folder (s, f1);

	return s;
}

void
maildir_free (SOURCE *src)
{
	free (src);
}
