#ifndef _M_RSS_H_
#define _M_RSS_H_

#include "source.h"

#define MAGIC_RSS ((7 << 8) + MAGIC_SOURCE)

typedef struct plugin_t PLUGIN;
typedef struct folder_t FOLDER;

extern PLUGIN rss_plugin;

typedef struct rss_source_t {
	SOURCE source;
	int num_feeds;
	FOLDER *feeds[10];
} RSS;

RSS * rss_create  (RSS *r);
void  rss_release (RSS *r);

#endif // _M_RSS_H_
