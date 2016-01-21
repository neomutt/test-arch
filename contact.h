#ifndef _M_CONTACT_H_
#define _M_CONTACT_H_

#include "item.h"

#define MAGIC_CONTACT ((2 << 8) + MAGIC_ITEM)

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

CONTACT * contact_create  (CONTACT *c);
void      contact_release (CONTACT *c);

#endif // _M_CONTACT_H_
