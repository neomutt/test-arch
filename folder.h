/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _FOLDER_H_
#define _FOLDER_H_

#include "container.h"

#define MAGIC_FOLDER 5

typedef struct item_t   ITEM;
typedef struct folder_t FOLDER;

typedef struct folder_t {
	CONTAINER container;
	int num_items;
	ITEM *items[10];
} FOLDER;

FOLDER * folder_create    (FOLDER *f);
void     folder_destroy   (FOLDER *f);
int      folder_add_child (FOLDER *f, void *child);
void     folder_display   (FOLDER *f, int indent);

#endif // _FOLDER_H_
