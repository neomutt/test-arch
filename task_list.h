#ifndef _M_TASK_LIST_H_
#define _M_TASK_LIST_H_

#include "source.h"

#define MAGIC_TASK_LIST ((9 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN task_list_plugin;

typedef struct task_list_source_t {
	SOURCE source;
} TASK_LIST;

TASK_LIST * task_list_create  (TASK_LIST *t);
void        task_list_release (TASK_LIST *t);

#endif // _M_TASK_LIST_H_
