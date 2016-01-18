#ifndef _PLUGIN_H_
#define _PLUGIN_H_

typedef struct source_t SOURCE;

typedef int      (*plugin_init_fn)       (void);
typedef SOURCE * (*plugin_connect_fn)    (void);
typedef void     (*plugin_disconnect_fn) (void);
typedef int      (*plugin_config_fn)     (const char *name);

typedef struct plugin_t {
	int                  magic;
	const char          *name;
	plugin_init_fn       init;
	plugin_connect_fn    connect;
	plugin_disconnect_fn disconnect;
	plugin_config_fn     config;
} PLUGIN;

extern PLUGIN *plugins[];

#endif // _PLUGIN_H_
