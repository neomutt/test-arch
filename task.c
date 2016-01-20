#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"

static int
task_release (TASK *t)
{
	if (!t) {
		return -1;
	}

	OBJECT *o = &t->item.object;
	o->refcount--;
	int rc = o->refcount;
	if (o->refcount < 1) {
		free (t->item.name);
		free (t);
	}

	return rc;
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
	o->release  = (object_release_fn) task_release;
	o->display  = (object_display_fn) item_display;

	return t;
}

