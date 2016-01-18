#include <stdio.h>
#include <string.h>

#include "config.h"
#include "plugin.h"
#include "view.h"

int
main (int argc, char *argv[])
{
	if (argc < 2) {
		printf ("Usage: %s CONFIG-FILE [...]\n", argv[0]);
		return 1;
	}

	int i;

	for (i = 0; plugins[i]; i++) {
		if (plugins[i]->init() == 0) {
			printf ("plugin %s::init() failed\n", plugins[i]->name);
		}
	}

	for (argc--; argc > 0; argc--, argv++) {
		config_read_file (argv[1], plugins);
	}

	VIEW *v = view_create();
	if (!v) {
		printf ("view_create failed\n");
		return 1;
	}

	v->name = strdup ("mail");

	for (i = 0; plugins[i]; i++) {
		SOURCE *s = plugins[i]->connect();
		if (!s) {
			printf ("plugin %s::connect() failed\n", plugins[i]->name);
		}
		view_add_source (v, s);
	}

	view_display (v, 0);

	object_release (v);
	config_free();

	return 0;
}

