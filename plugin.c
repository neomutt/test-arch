#include <stdio.h>

#include "plugin.h"
#include "imap.h"
#include "maildir.h"
#include "mbox.h"
#include "contact_list.h"
#include "task_list.h"
#include "nntp.h"
#include "rss.h"
#include "calendar.h"
#include "search_list.h"

PLUGIN *plugins[] = {
	&imap_plugin,
	&maildir_plugin,
	&mbox_plugin,
	&contact_list_plugin,
	&task_list_plugin,
	&nntp_plugin,
	&rss_plugin,
	&calendar_plugin,
	&search_list_plugin,
	NULL
};

