#include <stdio.h>

#include "config.h"

static int number;

int
config_read_file (const char *file)
{
	if (!file)
		return 0;

	FILE *f = fopen (file, "r");
	if (!f) {
		return -1;
	}

	char buffer[128];

	while (fgets (buffer, sizeof (buffer), f)) {
		number++;
	}
	// printf ("file '%s' has %d lines\n", file, number);

	fclose (f);
	return 0;
}

void
config_free (void)
{
	number = 0;
}

