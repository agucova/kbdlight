# The libraries to build
noinst_LIBRARIES = lib-base.a
noinst_HEADERS = lib_base.h

# The files to add to the library and to the source distribution
lib_base_a_SOURCES = \
                         $(lib_base_a_HEADERS) \
                         lib_base.c
if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall
endif
