#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "item.h"

typedef struct email_t {
	ITEM item;
	const char *from;
	const char *to;
	const char *subject;
} EMAIL;

#endif // _EMAIL_H_
