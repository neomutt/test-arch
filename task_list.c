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

void
task_list_release (TASK_LIST *t)
{
	if (!t) {
		return;
	}

	// Nothing TASK_LIST-specific to release

	source_release (&t->source);	// Release parent
}

TASK_LIST *
task_list_create (TASK_LIST *t)
{
	if (!t) {
		t = calloc (1, sizeof (TASK_LIST));
		if (!t) {
			return NULL;
		}
	}

	source_create (&t->source);	// Construct parent

	OBJECT *o = &t->source.container.object;

	o->type    = MAGIC_TASK_LIST;
	o->name    = strdup ("task list");
	o->release = (object_release_fn) task_list_release;

	return t;
}


static SOURCE *
task_list_init (void)
{
	TASK_LIST *ts = task_list_create (NULL);
	if (!ts) {
		return NULL;
	}

	return &ts->source;
}

static int
task_list_config_item (const char *name)
{
	if (!name) {
		return 0;
	}

	if ((name[0] >= 'u') && (name[0] <= 'x')) {
		// printf ("task config: %s\n", name);
		return 1;
	}

	return 0;
}

static void
task_list_connect (SOURCE *s)
{
	const char *names[] = { "ironing", "read book",          "plan holiday",       "play football", "get a suntan", NULL   };
	const T_TAGS tags[] = { T_INSIDE,  T_INSIDE | T_OUTSIDE, T_INSIDE | T_OUTSIDE, T_OUTSIDE,       T_OUTSIDE,      T_NONE };
	TASK *tasks[10];

	int i;

	for (i = 0; names[i]; i++) {
		tasks[i] = task_create (NULL);
		if (!tasks[i]) {
			printf ("task_list_connect: item_create failed\n");
			return NULL;
		}
		tasks[i]->item.object.name = strdup (names[i]);
		tasks[i]->tags             = tags[i];

		add_child (s, tasks[i]);	// Source owns all tasks
	}

	tasks[i] = NULL;

	FOLDER *f1 = folder_create (NULL);
	FOLDER *f2 = folder_create (NULL);
	FOLDER *f3 = folder_create (NULL);

	if (!f1 || !f2 || !f3) {
		printf ("task_list_connect: folder_create failed\n");
		return NULL;
	}

	f1->container.object.name = strdup ("inside");
	f2->container.object.name = strdup ("outside");
	f3->container.object.name = strdup ("untagged");

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags & T_INSIDE) {
			add_child (f1, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags & T_OUTSIDE) {
			add_child (f2, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		if (tasks[i]->tags == T_NONE) {
			add_child (f3, tasks[i]);
		}
	}

	for (i = 0; tasks[i]; i++) {
		release (tasks[i]);
	}

	add_child (s, f1);
	add_child (s, f2);
	add_child (s, f3);

	release (f1);
	release (f2);
	release (f3);
}

static void
task_list_disconnect (SOURCE *src)
{
	if (!src) {
		return;
	}
}


PLUGIN task_list_plugin = {
	MAGIC_TASK,
	"task",
	task_list_init,
	task_list_config_item,
	task_list_connect,
	task_list_disconnect
};

