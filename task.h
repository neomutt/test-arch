#ifndef _M_TASK_H_
#define _M_TASK_H_

#include "item.h"

#define MAGIC_TASK ((4 << 8) + MAGIC_ITEM)

typedef enum {
	T_NONE    = 0,
	T_INSIDE  = 1 << 0,
	T_OUTSIDE = 1 << 1
} T_TAGS;

typedef struct task_t {
	ITEM item;
	int tags;
} TASK;

TASK * task_create (void);

#endif // _M_TASK_H_
