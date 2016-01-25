/* Copyright (c) 2016 Richard Russon <rich@flatcap.org>
 * Released under the GPLv3 -- see LICENSE.md for details */

#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct config_t {
	int type;
} CONFIG;

typedef struct plugin_t PLUGIN;

int config_read_file (const char *file, PLUGIN **plugins);
void config_free (void);

#endif // _CONFIG_H_
