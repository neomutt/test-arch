#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "source.h"

VIEW *
view_create (void)
{
	VIEW *v = NULL;

	v = calloc (1, sizeof (VIEW));
	if (!v) {
		return NULL;
	}

	v->type = 234;

	return v;
}

void
view_free (VIEW *v)
{
	if (!v) {
		return;
	}

	int i;
	for (i = 0; i < v->num_sources; i++) {
		// printf ("freeing source %p\n", (void*) v->sources[i]);
		source_free (v->sources[i]);
	}

	free (v->name);
	free (v);
}

int
view_add_source (VIEW *v, SOURCE *src)
{
	if (!v || !src) {
		return 0;
	}

	v->sources[v->num_sources] = src;
	v->num_sources++;

	return 1;
}

void
view_display (VIEW *v)
{
	if (!v) {
		return;
	}

	printf ("\033[1;31m%s\033[m\n", v->name);
	int i;
	for (i = 0; i < v->num_sources; i++) {
		source_display (v->sources[i]);
	}
}

