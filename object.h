#ifndef _OBJECT_H_
#define _OBJECT_H_

typedef int  (*object_release_fn) (void *obj);
typedef void (*object_display_fn) (void *obj, int indent);

typedef struct object_t {
	int type;
	int refcount;
	char *name;
	object_release_fn release;
	object_display_fn display;
} OBJECT;

int  object_addref  (void *obj);
int  object_release (void *obj);
void object_display (void *obj, int indent);

#endif // _OBJECT_H_
