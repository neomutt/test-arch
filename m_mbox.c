#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

int
mbox_init (void)
{
	printf ("mbox init\n");
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

	s->type = 123;

	return s;
}

void
mbox_free (SOURCE *src)
{
	free (src);
}
