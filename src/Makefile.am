if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -O3
endif

bin_PROGRAMS = kbdlight
kbdlight_SOURCES = main.c

kbdlight_LDADD = $(top_builddir)/src/lib/libbase.a $(AM_LDFLAGS)