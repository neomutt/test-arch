#ifndef _FOLDER_H_
#define _FOLDER_H_

#include "object.h"

#define MAGIC_FOLDER 3

typedef struct item_t ITEM;

typedef struct folder_t {
	OBJECT object;
	int num_folders;
	struct folder_t *folders[10];
	int num_items;
	ITEM *items[10];
} FOLDER;

FOLDER * folder_create (void);
int folder_add_child (FOLDER *f, void *child);

#endif // _FOLDER_H_
