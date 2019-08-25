if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall
endif


# The libraries to build
noinst_LIBRARIES = libbase.a
noinst_HEADERS = dir.h file.h text.h

# The files to add to the library and to the source distribution
libbase_a_SOURCES = $(libbase_a_HEADERS) dir.c file.c text.c