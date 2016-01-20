#ifndef _M_CALENDAR_H_
#define _M_CALENDAR_H_

#include "source.h"

#define MAGIC_CALENDAR ((7 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN calendar_plugin;

typedef struct calendar_source_t {
	SOURCE source;
} CALENDAR_SOURCE;

#endif // _M_CALENDAR_H_
