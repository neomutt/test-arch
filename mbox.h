/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _M_MBOX_H_
#define _M_MBOX_H_

#include "source.h"

#define MAGIC_MBOX ((5 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN mbox_plugin;

typedef struct mbox_source_t {
	SOURCE source;
} MBOX;

MBOX * mbox_create  (MBOX *m);
void   mbox_destroy (MBOX *m);

#endif // _M_MBOX_H_
