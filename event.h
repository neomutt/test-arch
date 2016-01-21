#ifndef _EVENT_H_
#define _EVENT_H_

#include "item.h"

#define MAGIC_EVENT ((4 << 8) + MAGIC_ITEM)

typedef struct event_t {
	ITEM item;
	int day;
} EVENT;

EVENT * event_create  (EVENT *e);
void    event_release (EVENT *e);

#endif // _EVENT_H_
