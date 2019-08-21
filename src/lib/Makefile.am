if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall
endif


# The libraries to build
noinst_LIBRARIES = lib-base.a

# The files to add to the library and to the source distribution
lib_base_a_SOURCES = \
										     $(lib_base_a_HEADERS) \
										     lib-base.c