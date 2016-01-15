#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct config_t {
	int type;
} CONFIG;

int config_read_file (const char *file);
void config_free (void);

#endif // _CONFIG_H_
