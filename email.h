#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "item.h"

#define MAGIC_EMAIL ((5 << 8) + MAGIC_ITEM)

typedef struct email_t {
	ITEM item;
	char *from;
	char *to;
	char *subject;
} EMAIL;

EMAIL * email_create (void);

#endif // _EMAIL_H_
