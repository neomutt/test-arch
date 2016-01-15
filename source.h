#ifndef _SOURCE_H_
#define _SOURCE_H_

typedef struct folder_t FOLDER;

typedef struct source_t {
	int type;
	char *name;
	int num_folders;
	FOLDER *folders[10];
} SOURCE;

void source_free (SOURCE *src);
int source_add_folder (SOURCE *src, FOLDER *f);
void source_display (SOURCE *src, int indent);

#endif // _SOURCE_H_
