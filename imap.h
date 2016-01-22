#ifndef _M_IMAP_H_
#define _M_IMAP_H_

#include "source.h"

#define MAGIC_IMAP ((3 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN imap_plugin;

typedef struct imap_source_t {
	SOURCE source;
} IMAP;

IMAP * imap_create  (IMAP *i);
void   imap_destroy (IMAP *i);

#endif // _M_IMAP_H_
