#include <stdio.h>

#include "plugin.h"
#include "imap.h"
#include "maildir.h"
#include "mbox.h"
#include "contact.h"

PLUGIN *plugins[] = {
	// &imap_plugin,
	// &maildir_plugin,
	// &mbox_plugin,
	&contact_plugin,
	NULL
};

