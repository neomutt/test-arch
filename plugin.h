/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

typedef struct source_t SOURCE;

typedef SOURCE * (*plugin_init_fn)       (void);
typedef int      (*plugin_config_fn)     (const char *name);
typedef void     (*plugin_connect_fn)    (SOURCE *src);
typedef void     (*plugin_disconnect_fn) (SOURCE *src);

typedef struct plugin_t {
	int                  magic;
	const char          *name;
	plugin_init_fn       init;
	plugin_config_fn     config;
	plugin_connect_fn    connect;
	plugin_disconnect_fn disconnect;
} PLUGIN;

extern PLUGIN *plugins[];

#endif // _PLUGIN_H_
