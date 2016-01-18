#ifndef _VIEW_H_
#define _VIEW_H_

#include "object.h"

typedef struct source_t SOURCE;

typedef struct view_t {
	OBJECT object;
	char *name;
	int num_sources;
	SOURCE *sources[10];
} VIEW;

VIEW * view_create (void);
int view_add_source (VIEW *v, SOURCE *src);
void view_display (VIEW *v, int indent);

#endif // _VIEW_H_
