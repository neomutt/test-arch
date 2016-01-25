/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "plugin.h"

int
config_read_file (const char *file, PLUGIN **plugins)
{
	if (!file)
		return 0;

	FILE *f = fopen (file, "r");
	if (!f) {
		return -1;
	}

	char buffer[128];
	int i;
	int len;

	while (fgets (buffer, sizeof (buffer), f)) {
		len = strnlen (buffer, sizeof (buffer));
		if (len > 0) {
			len--;
		}
		buffer[len] = 0;

		for (i = 0; plugins[i]; i++) {
			if (plugins[i]->config (buffer) == 1) {
				break;
			}
		}

		if (!plugins[i]) {
			// printf ("Unknown config: %s\n", buffer);
		}
	}

	fclose (f);
	return 0;
}

void
config_free (void)
{
}

