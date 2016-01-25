/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#define MAGIC_OBJECT 1

typedef void (*object_destroy_fn) (void *obj);
typedef void (*object_display_fn) (void *obj, int indent);

typedef struct object_t {
	int type;
	int refcount;
	char *name;
	object_destroy_fn destroy;
	object_display_fn display;
} OBJECT;

OBJECT * object_create  (OBJECT *obj);
void     object_destroy (OBJECT *obj);
void     object_display (OBJECT *obj, int indent);

int  addref  (void *obj);
int  release (void *obj);
void display (void *obj, int indent);

#endif // _OBJECT_H_
