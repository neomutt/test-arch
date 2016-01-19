#ifndef _M_MBOX_H_
#define _M_MBOX_H_

#include "source.h"

#define MAGIC_MBOX ((4 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN mbox_plugin;

typedef struct mbox_source_t {
	SOURCE source;
} MBOX_SOURCE;

#endif // _M_MBOX_H_
