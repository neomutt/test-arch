#ifndef _FOLDER_H_
#define _FOLDER_H_

#include "object.h"

typedef struct item_t ITEM;

typedef struct folder_t {
	OBJECT object;
	char *name;
	int num_folders;
	struct folder_t *folders[10];
	int num_items;
	ITEM *items[10];
} FOLDER;

FOLDER * folder_create (void);
int folder_add_folder (FOLDER *f, FOLDER *child);
int folder_add_item (FOLDER *f, ITEM *i);
void folder_display (FOLDER *f, int indent);

#endif // _FOLDER_H_
