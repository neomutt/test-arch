#ifndef _M_MBOX_H_
#define _M_MBOX_H_

extern const int MAGIC_MBOX;

typedef struct source_t SOURCE;

int      mbox_init (void);
SOURCE * mbox_connect (void);
void     mbox_free (SOURCE *src);

#endif // _M_MBOX_H_
