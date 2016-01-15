#ifndef _M_IMAP_H_
#define _M_IMAP_H_

extern const int MAGIC_IMAP;

typedef struct source_t SOURCE;

int      imap_init (void);
SOURCE * imap_connect (void);
void     imap_free (SOURCE *src);

#endif // _M_IMAP_H_
