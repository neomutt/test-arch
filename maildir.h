#ifndef _M_MAILDIR_H_
#define _M_MAILDIR_H_

#include "source.h"

#define MAGIC_MAILDIR ((4 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN maildir_plugin;

typedef struct maildir_source_t {
	SOURCE source;
} MAILDIR_SOURCE;

MAILDIR_SOURCE * maildir_create  (MAILDIR_SOURCE *m);
void             maildir_release (MAILDIR_SOURCE *m);

#endif // _M_MAILDIR_H_
