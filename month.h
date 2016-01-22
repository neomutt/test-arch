#ifndef _M_MONTH_H_
#define _M_MONTH_H_

#include "folder.h"

#define MAGIC_MONTH ((1 << 8) + MAGIC_FOLDER)

typedef struct plugin_t PLUGIN;

extern PLUGIN month_plugin;

typedef struct month_t {
	FOLDER folder;
	int year;
	int month;
} MONTH;

MONTH * month_create    (MONTH *m);
void    month_destroy   (MONTH *m);
int     month_add_child (MONTH *m, void *child);
void    month_display   (MONTH *m, int indent);

#endif // _M_MONTH_H_
