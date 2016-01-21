#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"

void
task_release (TASK *t)
{
	if (!t) {
		return;
	}

	// Nothing TASK-specific to release

	item_release (&t->item);	// Release parent
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
	o->release  = (object_release_fn) task_release;

	return t;
}

