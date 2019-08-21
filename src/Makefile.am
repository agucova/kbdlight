if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -O3
endif

bin_PROGRAMS = kdblight
kdblight_SOURCES = main.c

kdblight_LDADD = $(top_builddir)/src/lib/lib-base.a $(AM_LDFLAGS)