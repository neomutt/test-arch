#ifndef _M_SEARCH_LIST_H_
#define _M_SEARCH_LIST_H_

#include "source.h"

#define MAGIC_SEARCH_LIST ((8 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN search_list_plugin;

typedef struct search_list_source_t {
	SOURCE source;
} SEARCH_LIST_SOURCE;

#endif // _M_SEARCH_LIST_H_
