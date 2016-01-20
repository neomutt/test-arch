#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "object.h"
#include "item.h"

#define MAGIC_SOURCE 2

typedef struct folder_t FOLDER;

typedef struct source_t {
	OBJECT object;
	int num_folders;
	FOLDER *folders[10];
	int num_items;
	ITEM *items[10];
} SOURCE;

SOURCE * source_create (void);
int source_add_child (SOURCE *src, void *child);
void source_display (SOURCE *src, int indent);

#endif // _SOURCE_H_
