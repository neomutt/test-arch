#ifndef _SOURCE_H_
#define _SOURCE_H_

typedef struct source_t {
	int type;
} SOURCE;

void source_free (SOURCE *src);

#endif // _SOURCE_H_
