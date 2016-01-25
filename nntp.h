/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _M_NNTP_H_
#define _M_NNTP_H_

#include "source.h"

#define MAGIC_NNTP ((6 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN nntp_plugin;

typedef struct nntp_source_t {
	SOURCE source;
} NNTP;

NNTP * nntp_create  (NNTP *n);
void   nntp_destroy (NNTP *n);

#endif // _M_NNTP_H_
