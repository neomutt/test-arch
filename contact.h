#ifndef _M_CONTACT_H_
#define _M_CONTACT_H_

#include "item.h"

#define MAGIC_CONTACT ((1 << 8) + MAGIC_ITEM)

typedef struct plugin_t PLUGIN;

extern PLUGIN contact_plugin;

typedef enum {
	C_NONE   = 0,
	C_COUNTY = 1 << 0,
	C_ANIMAL = 1 << 1,
	C_CAR    = 1 << 2
} C_TAGS;

typedef struct contact_t {
	ITEM item;
	int tags;
} CONTACT;

#endif // _M_CONTACT_H_
