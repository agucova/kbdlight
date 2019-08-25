if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/helpers -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/helpers -Wall
endif


# The libraries to build
noinst_LIBRARIES = helpers.a
noinst_HEADERS = dir.h file.h text.h

# The files to add to the library and to the source distribution
helper_a_SOURCES = $(helper_a_HEADERS) dir.c file.c text.c1