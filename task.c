#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"

void
task_destroy (TASK *t)
{
	if (!t) {
		return;
	}

	// Nothing TASK-specific to release

	item_destroy (&t->item);	// Destroy parent
}

TASK *
task_create (TASK *t)
{
	if (!t) {
		t = calloc (1, sizeof (TASK));
		if (!t) {
			return NULL;
		}
	}

	item_create (&t->item);	// Construct parent

	OBJECT *o = &t->item.object;

	o->type     = MAGIC_TASK;
	o->destroy  = (object_destroy_fn) task_destroy;

	return t;
}

