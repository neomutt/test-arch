#include <stdio.h>
#include <stdlib.h>

#include "item.h"

void
item_free (ITEM *i)
{
	if (!i) {
		return;
	}

	free (i->name);
	free (i);
}

void
item_display (ITEM *i)
{
	if (!i) {
		return;
	}

	printf ("\t\t\t%s\n", i->name);
}

