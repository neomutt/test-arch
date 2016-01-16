#include <stdio.h>
#include <stdlib.h>

#include "item.h"

void
item_free (ITEM *i)
{
	if (!i) {
		return;
	}

	OBJECT *o = &i->object;
	if (o->delete) {
		(*o->delete)();
	} else {
		free (i->name);
		free (i);
	}
}

void
item_display (ITEM *i, int indent)
{
	if (!i) {
		return;
	}

	printf ("%*s\033[1;36m%s\033[m\n", indent * 8, "", i->name);
}

