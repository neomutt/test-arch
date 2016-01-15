#ifndef _VIEW_H_
#define _VIEW_H_

typedef struct source_t SOURCE;

typedef struct view_t {
	int type;
	int num_sources;
	SOURCE *sources[10];
} VIEW;

VIEW * view_create (void);
void view_free (VIEW *v);
int view_add_source (VIEW *v, SOURCE *src);

#endif // _VIEW_H_
