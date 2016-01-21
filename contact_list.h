#ifndef _M_CONTACT_LIST_H_
#define _M_CONTACT_LIST_H_

#include "source.h"

#define MAGIC_CONTACT_LIST ((2 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;

extern PLUGIN contact_list_plugin;

typedef struct contact_list_source_t {
	SOURCE source;
} CONTACT_LIST_SOURCE;

CONTACT_LIST_SOURCE * contact_list_create  (CONTACT_LIST_SOURCE *c);
void                  contact_list_release (CONTACT_LIST_SOURCE *c);

#endif // _M_CONTACT_LIST_H_
