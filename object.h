#ifndef _OBJECT_H_
#define _OBJECT_H_

typedef void (*object_delete_fn) (void);

typedef struct object_t {
	int type;
	int refcount;
	object_delete_fn *delete;
} OBJECT;

#endif // _OBJECT_H_
