#ifndef _FOLDER_H_
#define _FOLDER_H_

typedef struct item_t ITEM;

typedef struct folder_t {
	int type;
	char *name;
	int num_folders;
	struct folder_t *folders[10];
	int num_items;
	ITEM *items[10];
} FOLDER;

void folder_free (FOLDER *f);
int folder_add_folder (FOLDER *f, FOLDER *child);
int folder_add_item (FOLDER *f, ITEM *i);
void folder_display (FOLDER *f, int indent);

#endif // _FOLDER_H_
