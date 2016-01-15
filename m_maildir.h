#ifndef _M_MAILDIR_H_
#define _M_MAILDIR_H_

typedef struct source_t SOURCE;

int      maildir_init (void);
SOURCE * maildir_connect (void);
void     maildir_free (SOURCE *src);

#endif // _M_MAILDIR_H_
