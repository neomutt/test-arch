#ifndef _VIEW_H_
#define _VIEW_H_

#include "object.h"

#define MAGIC_VIEW 1

typedef struct source_t SOURCE;

typedef struct view_t {
	OBJECT object;
	char *name;
	int num_sources;
	SOURCE *sources[10];
} VIEW;

VIEW * view_create (void);
int view_add_child (VIEW *v, void *child);

#endif // _VIEW_H_
