#ifndef _M_NNTP_H_
#define _M_NNTP_H_

#include "source.h"

#define MAGIC_NNTP ((6 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN nntp_plugin;

typedef struct nntp_source_t {
	SOURCE source;
} NNTP_SOURCE;

NNTP_SOURCE * nntp_create  (NNTP_SOURCE *n);
void          nntp_release (NNTP_SOURCE *n);

#endif // _M_NNTP_H_
