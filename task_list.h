#ifndef _M_TASK_LIST_H_
#define _M_TASK_LIST_H_

#include "source.h"

#define MAGIC_TASK_LIST ((6 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN task_list_plugin;

typedef struct task_list_source_t {
	SOURCE source;
} TASK_LIST_SOURCE;

#endif // _M_TASK_LIST_H_
