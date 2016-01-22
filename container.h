#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "object.h"

#define MAGIC_CONTAINER 2

typedef struct container_t CONTAINER;

typedef int (*container_add_child_fn) (CONTAINER *c, void *child);

typedef struct container_t {
	OBJECT object;
	container_add_child_fn add_child;
	int num_children;
	CONTAINER *children[10];
} CONTAINER;

CONTAINER * container_create    (CONTAINER *c);
void        container_destroy   (CONTAINER *c);
int         container_add_child (CONTAINER *c, void *child);
void        container_display   (CONTAINER *c, int indent);

int add_child (void *parent, void *child);

#endif // _CONTAINER_H_
