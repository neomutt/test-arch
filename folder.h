#ifndef _FOLDER_H_
#define _FOLDER_H_

typedef struct item_t ITEM;

typedef struct folder_t {
	int type;
	char *name;
	int num_items;
	ITEM *items[10];
} FOLDER;

void folder_free (FOLDER *f);
int folder_add_item (FOLDER *f, ITEM *i);

#endif // _FOLDER_H_
