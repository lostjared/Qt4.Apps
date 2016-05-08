bin_PROGRAMS = aftool
aftool_SOURCES = aftool.c

# set the include path found by configure
INCLUDES=-I$(_PREFIX)/include $(all_includes)
GD=-lgd

# the library search path.
aftool_LDFLAGS = $(all_libraries) $(GD) -L$(_PREFIX)/lib -lpng12 -lz 

