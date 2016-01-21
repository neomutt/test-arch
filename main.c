#include <stdio.h>
#include <string.h>

#include "config.h"
#include "plugin.h"
#include "view.h"
#include "source.h"

int
main (int argc, char *argv[])
{
	if (argc < 2) {
		printf ("Usage: %s CONFIG-FILE [...]\n", argv[0]);
		return 1;
	}

	int i;

	SOURCE *sources[10];

	for (i = 0; plugins[i]; i++) {
		sources[i] = plugins[i]->init();
		if (sources[i] == NULL) {
			printf ("plugin %s::init() failed\n", plugins[i]->name);
			return 1;
		}
	}
	sources[i] = NULL;

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

	v1->object.name = strdup ("mail");
	v2->object.name = strdup ("search");
	v3->object.name = strdup ("contacts");
	v4->object.name = strdup ("tasks");
	v5->object.name = strdup ("news");
	v6->object.name = strdup ("calendar");

	SOURCE *search = sources[3];

	for (i = 0; plugins[i]; i++) {
		SOURCE *s = sources[i];

		plugins[i]->connect (s);
		// if (!s) {
		// 	printf ("plugin %s::connect() failed\n", plugins[i]->name);
		// }
		switch (i) {
			case 0:
			case 1:
			case 2:
				view_add_child (v1, s);
				source_add_child (search, s);
				break;
			case 3:
				view_add_child (v2, s);
				break;
			case 4:
				view_add_child (v3, s);
				break;
			case 5:
				view_add_child (v4, s);
				break;
			case 6:
			case 7:
				view_add_child (v5, s);
				break;
			default:
				view_add_child (v6, s);
				break;
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

