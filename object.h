#ifndef _OBJECT_H_
#define _OBJECT_H_

#define MAGIC_OBJECT 1

typedef void (*object_release_fn) (void *obj);
typedef void (*object_display_fn) (void *obj, int indent);

typedef struct object_t {
	int type;
	int refcount;
	char *name;
	object_release_fn release;
	object_display_fn display;
} OBJECT;

OBJECT * object_create  (OBJECT *obj);
int      object_addref  (OBJECT *obj);
void     object_release (OBJECT *obj);
void     object_display (OBJECT *obj, int indent);

int release (void *obj);

#endif // _OBJECT_H_
