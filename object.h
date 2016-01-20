#ifndef _OBJECT_H_
#define _OBJECT_H_

typedef int (*object_release_fn) (void*);

typedef struct object_t {
	int type;
	int refcount;
	object_release_fn release;
} OBJECT;

int object_addref  (void *obj);
int object_release (void *obj);

#endif // _OBJECT_H_
