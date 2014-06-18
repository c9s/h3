TESTS =

AM_CFLAGS=$(DEPS_CFLAGS) $(GVC_DEPS_CFLAGS) $(JSONC_CFLAGS) @CHECK_CFLAGS@ -I$(top_builddir) -I$(top_builddir)/include -I$(top_builddir)/src -I$(top_builddir)/3rdparty  -Wall -std=c99 -ggdb -Wall
AM_LDFLAGS=$(DEPS_LIBS) $(GVC_DEPS_LIBS) $(JSONC_LIBS) @CHECK_LIBS@ $(top_builddir)/libh3.la

noinst_HEADERS = $(NULL)

dist_noinst_DATA = $(NULL)

TESTS += check_parser
check_slug_SOURCES = check_parser.c

check_PROGRAMS = $(TESTS)

# noinst_PROGRAMS = bench
# bench_SOURCES = bench.c

# AM_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir)/include
# AM_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir) -I$(top_builddir)/include
# CLEANFILES                  = check_tree.log
