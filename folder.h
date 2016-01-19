#ifndef _FOLDER_H_
#define _FOLDER_H_

#include "object.h"

extern const int MAGIC_FOLDER;

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
int folder_add_child (FOLDER *f, void *child);
void folder_display (FOLDER *f, int indent);

#endif // _FOLDER_H_
