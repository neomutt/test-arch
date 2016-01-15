#include <stdio.h>
#include <stdlib.h>

#include "source.h"

void
source_free (SOURCE *src)
{
	if (!src) {
		return;
	}

	free (src);
}

