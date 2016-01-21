#ifndef _VIEW_H_
#define _VIEW_H_

#include "container.h"

#define MAGIC_VIEW 3

typedef struct source_t SOURCE;

typedef struct view_t {
	CONTAINER container;
} VIEW;

VIEW * view_create    (VIEW *v);
int    view_add_child (VIEW *v, void *child);
void   view_display   (VIEW *v, int indent);

#endif // _VIEW_H_
