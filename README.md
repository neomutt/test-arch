# Arch

## What is it?

This is a sample application showing what I'd like mutt to look like: a set of
objects with inheritance; virtual functions; reference counting.

## Why?

The mutt code is a mass of interdependent components which all rely on global
variables.

Mutt needs to be broken up to give better independence between components.
This will make mutt more robust and easier to maintain.

## What am I looking at?

This is the inheritance graph for the objects in the application.

![inheritance](https://flatcap.org/mutt/arch.png)

To understand how the objects fit together, start with the **source**s.  Each
**source** represents one connection to a data source: 1 imap connection, 1
contact list, etc.

The **source**s store their data in **item**s, which can be grouped into
**folder**s.  A **folder** can represent a real directory, or something virtual
like a tag.  Because all the **object**s are reference counted, the **item**s
can appear in zero, one or multiple **folder**s.  Because of the inheritance
(in theory) an **email** object could be passed between **source**s.

**source**s are owned by **view**s.  A **view** may contain multiple
**source**s, e.g.  several email servers, multiple contact lists.  The
**view**s directly map onto what gets displayed on screen (and would fit into
my panel manager ideally).

## Plugins

The application has a sample **source** for every text-based information source
I thought useful.

* Email:
  * imap
  * maildir
  * mbox
  * notmuch (search engine)

* News:
  * NNTP (usenet)
  * RSS

* General office:
  * Contact list
  * Task lists
  * Calendar

## Who?

* Rich Russon (FlatCap) &lt;rich@flatcap.org&gt;
* https://flatcap.org/

![flatcap](https://flatcap.org/gfx/flatcap.png)

## License

The code is released under the GPLv3. 
See [LICENSE.md](https://github.com/neomutt/arch/blob/master/LICENSE.md) for more details.

