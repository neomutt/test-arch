#include <stdio.h>
#include <string.h>

#include "config.h"
#include "m_imap.h"
#include "m_maildir.h"
#include "m_mbox.h"
#include "view.h"

int
main (int argc, char *argv[])
{
	if (argc < 2) {
		printf ("Usage: %s CONFIG-FILE [...]\n", argv[0]);
		return 1;
	}

	imap_init();
	maildir_init();
	mbox_init();

	for (argc--; argc > 0; argc--, argv++) {
		config_read_file (argv[1]);
	}

	SOURCE *s_imap = imap_connect();
	if (!s_imap) {
		printf ("imap init failed\n");
		return 1;
	}

	SOURCE *s_maildir = maildir_connect();
	if (!s_maildir) {
		printf ("maildir init failed\n");
		return 1;
	}

	SOURCE *s_mbox = mbox_connect();
	if (!s_mbox) {
		printf ("mbox init failed\n");
		return 1;
	}

	VIEW *v = view_create();
	if (!v) {
		printf ("view_create failed\n");
		return 1;
	}

	v->name = strdup ("mail");

	view_add_source (v, s_imap);
	view_add_source (v, s_maildir);
	view_add_source (v, s_mbox);

	view_display (v);

	view_free (v);
	config_free();

	return 0;
}

