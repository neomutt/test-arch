#ifndef _M_NNTP_H_
#define _M_NNTP_H_

#include "source.h"

#define MAGIC_NNTP ((5 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN nntp_plugin;

typedef struct nntp_source_t {
	SOURCE source;
} NNTP_SOURCE;

#endif // _M_NNTP_H_
