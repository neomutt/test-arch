#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"

static void
task_free (TASK *t)
{
	if (!t) {
		return;
	}

	OBJECT *o = &t->item.object;
	o->refcount--;
	if (o->refcount < 1) {
		free (t->item.name);
		free (t);
	}
}

TASK *
task_create (void)
{
	TASK *t = NULL;

	t = calloc (1, sizeof (TASK));
	if (!t) {
		return NULL;
	}

	OBJECT *o = &t->item.object;

	o->refcount = 1;
	o->type     = MAGIC_TASK;
	o->release  = (object_release_fn) task_free;

	return t;
}

