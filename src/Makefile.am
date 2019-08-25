if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/helpers -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/helpers -Wall -O3
endif

bin_PROGRAMS = kdblight
kdblight_SOURCES = main.c

kdblight_LDADD = $(top_builddir)/src/helpers/helpers.a $(AM_LDFLAGS)