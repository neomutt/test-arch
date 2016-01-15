#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

const int MAGIC_MBOX = 234;

int
mbox_init (void)
{
	// printf ("mbox init\n");
	return 1;
}

SOURCE *
mbox_connect (void)
{
	SOURCE *s = NULL;

	s = calloc (1, sizeof (SOURCE));
	if (!s) {
		return NULL;
	}

	s->type = MAGIC_MBOX;
	s->name = strdup ("mbox");

	return s;
}

void
mbox_free (SOURCE *src)
{
	free (src);
}
