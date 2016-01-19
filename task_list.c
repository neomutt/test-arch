#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"
#include "task_list.h"
#include "folder.h"
#include "item.h"
#include "plugin.h"
#include "source.h"
#include "view.h"

// static char *config[10];

int
task_list_init (void)
{
	// printf ("task_list init\n");
	return 1;
}

SOURCE *
task_list_connect (void)
{
	SOURCE *s = NULL;

	s = source_create();
	if (!s) {
		return NULL;
	}

	s->object.type = MAGIC_TASK_LIST;
	s->name        = strdup ("task list");

	// Pretend to read something

	const char *names[] = { "ironing", "read book",          "plan holiday",       "play football", "get a suntan", NULL   };
	const T_TAGS tags[] = { T_INSIDE,  T_INSIDE | T_OUTSIDE, T_INSIDE | T_OUTSIDE, T_OUTSIDE,       T_OUTSIDE,      T_NONE };
	TASK *tasks[10];

	int i;

	for (i = 0; names[i]; i++) {
		tasks[i] = task_create();
		if (!tasks[i]) {
			printf ("task_list_connect: item_create failed\n");
			return NULL;
		}
		tasks[i]->item.name = strdup (names[i]);
		tasks[i]->tags      = tags[i];

		source_add_child (s, tasks[i]);	// Source owns all items
	}

	tasks[i] = NULL;

	FOLDER *f1 = folder_create();
	FOLDER *f2 = folder_create();
	FOLDER *f3 = folder_create();

	if (!f1 || !f2 || !f3) {
		printf ("task_list_connect: folder_create failed\n");
		return NULL;
	}

	f1->name = strdup ("inside");
	f2->name = strdup ("outside");
	f3->name = strdup ("untagged");

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags & T_INSIDE) {
			folder_add_child (f1, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags & T_OUTSIDE) {
			folder_add_child (f2, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags == T_NONE) {
			folder_add_child (f3, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		object_release (tasks[i]);
	}

	source_add_child (s, f1);
	source_add_child (s, f2);
	source_add_child (s, f3);

	object_release (f1);
	object_release (f2);
	object_release (f3);

	return s;
}

int
task_list_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'n') && (name[0] <= 'w')) {
		// printf ("task config: %s\n", name);
		return 1;
	}

	return 0;
}

void
task_list_disconnect (void)
{
}

PLUGIN task_list_plugin = {
	MAGIC_TASK,
	"task",
	task_list_init,
	task_list_connect,
	task_list_disconnect,
	task_list_config_item
};

