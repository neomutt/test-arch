#ifndef _ITEM_H_
#define _ITEM_H_

typedef struct item_t {
	int type;
	char *name;
} ITEM;

void item_free (ITEM *i);

#endif // _ITEM_H_
