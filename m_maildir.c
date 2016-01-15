#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

const int MAGIC_MAILDIR = 345;

int
maildir_init (void)
{
	printf ("maildir init\n");
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

	return s;
}

void
maildir_free (SOURCE *src)
{
	free (src);
}
