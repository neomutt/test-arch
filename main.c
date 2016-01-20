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

	VIEW *v1 = view_create();
	VIEW *v2 = view_create();
	VIEW *v3 = view_create();
	VIEW *v4 = view_create();
	VIEW *v5 = view_create();
	VIEW *v6 = view_create();
	if (!v1 || !v2 || !v3 || !v4 || !v5 || !v6) {
		printf ("view_create failed\n");
		return 1;
	}

	v1->name = strdup ("mail");
	v2->name = strdup ("contacts");
	v3->name = strdup ("tasks");
	v4->name = strdup ("news");
	v5->name = strdup ("calendar");
	v6->name = strdup ("search");

	for (i = 0; plugins[i]; i++) {
		SOURCE *s = plugins[i]->connect();
		if (!s) {
			printf ("plugin %s::connect() failed\n", plugins[i]->name);
		}
		if (i < 3) {
			view_add_child (v1, s);
		} else if (i < 4) {
			view_add_child (v2, s);
		} else if (i < 5) {
			view_add_child (v3, s);
		} else if (i < 7) {
			view_add_child (v4, s);
		} else if (i < 8) {
			view_add_child (v5, s);
		} else {
			view_add_child (v6, s);
		}
		object_release (s);
	}

	object_display (v1, 0);
	object_display (v2, 0);
	object_display (v3, 0);
	object_display (v4, 0);
	object_display (v5, 0);
	object_display (v6, 0);

	object_release (v1);
	object_release (v2);
	object_release (v3);
	object_release (v4);
	object_release (v5);
	object_release (v6);
	config_free();

	return 0;
}

