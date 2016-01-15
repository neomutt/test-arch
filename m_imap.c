#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

int
imap_init (void)
{
	printf ("IMAP init\n");
	return 1;
}

SOURCE *
imap_connect (void)
{
	SOURCE *s = NULL;

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	s->type = 123;

	return s;
}

void
imap_free (SOURCE *src)
{
	free (src);
}
