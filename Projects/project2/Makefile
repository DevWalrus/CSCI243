#
# Created by gmakemake (Ubuntu Jul 25 2014) on Fri Nov 19 21:33:43 2021
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

#
# NOTE: Makefile does not support ~/ for -L or -I; using $(HOME) 
#
INCLUDEPATH = /home/course/csci243/pub/projects/02/include
#
# CPPFLAGS= -I $(INCLUDEPATH)
CFLAGS= -std=c99 -ggdb -Wall -Wextra -pedantic -I $(INCLUDEPATH)
#
# public project2 archive
#
LIBPATH = /home/course/csci243/pub/projects/02/lib 

#
CLIBFLAGS = -lm -L$(LIBPATH) -lp2


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	packman.c packman_my_utils.c test-rw-treefile.c
PS_FILES =	
S_FILES =	
H_FILES =	HeapDT.h packman_my_utils.h packman_utils.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	packman_my_utils.o 

#
# Main targets
#

all:	packman test-rw-treefile 

packman:	packman.o $(OBJFILES)
	$(CC) $(CFLAGS) -o packman packman.o $(OBJFILES) $(CLIBFLAGS)

test-rw-treefile:	test-rw-treefile.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test-rw-treefile test-rw-treefile.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

packman.o:	packman_my_utils.h packman_utils.h
packman_my_utils.o:	HeapDT.h packman_my_utils.h packman_utils.h
test-rw-treefile.o:	packman_utils.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) packman.o test-rw-treefile.o core

realclean:        clean
	-/bin/rm -f packman test-rw-treefile 
