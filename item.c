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
