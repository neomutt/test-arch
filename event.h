#ifndef _EVENT_H_
#define _EVENT_H_

#include "item.h"

#define MAGIC_EVENT ((5 << 8) + MAGIC_ITEM)

typedef struct event_t {
	ITEM item;
} EVENT;

EVENT * event_create (void);

#endif // _EVENT_H_
