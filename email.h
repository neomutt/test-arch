#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "item.h"

#define MAGIC_EMAIL ((3 << 8) + MAGIC_ITEM)

typedef struct email_t {
	ITEM item;
	char *from;
	char *to;
	char *subject;
} EMAIL;

EMAIL * email_create  (EMAIL *e);
void    email_destroy (EMAIL *e);

#endif // _EMAIL_H_
