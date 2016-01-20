#ifndef _M_MONTH_H_
#define _M_MONTH_H_

#include "folder.h"

#define MAGIC_MONTH ((1 << 8) + MAGIC_FOLDER)

typedef struct plugin_t PLUGIN;

extern PLUGIN month_plugin;

typedef struct month_folder_t {
	FOLDER folder;
} MONTH_FOLDER;

MONTH_FOLDER * month_folder_create (void);

#endif // _M_MONTH_H_
