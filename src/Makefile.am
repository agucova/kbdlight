AM_CFLAGS = -I$(top_srcdir)/src

bin_PROGRAMS = kdblight
kdblight_SOURCES = main.c

if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src -I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src -I$(top_srcdir)/src/lib -Wall -O3
endif
