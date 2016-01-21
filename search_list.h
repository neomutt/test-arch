#ifndef _M_SEARCH_LIST_H_
#define _M_SEARCH_LIST_H_

#include "source.h"

#define MAGIC_SEARCH_LIST ((8 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN search_list_plugin;

typedef struct search_list_source_t {
	SOURCE source;
	int num_sources;
	SOURCE *sources[10];
} SEARCH_LIST_SOURCE;

SEARCH_LIST_SOURCE * search_list_create    (SEARCH_LIST_SOURCE *s);
void                 search_list_release   (SEARCH_LIST_SOURCE *s);
int                  search_list_add_child (SEARCH_LIST_SOURCE *s, void *child);

#endif // _M_SEARCH_LIST_H_
