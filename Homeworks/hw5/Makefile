#
# Created by gmakemake (Ubuntu Jul 25 2014) on Thu Oct 14 17:32:25 2021
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


CFLAGS= -std=c99 -ggdb -Wall -Wextra -pedantic -Werror

CLIBFLAGS= -lm 

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	hpcalc.c process.c stack.c
PS_FILES =	
S_FILES =	
H_FILES =	process.h stack.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	process.o stack.o 

#
# Main targets
#

all:	hpcalc 

hpcalc:	hpcalc.o $(OBJFILES)
	$(CC) $(CFLAGS) -o hpcalc hpcalc.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

hpcalc.o:	process.h stack.h
process.o:	
stack.o:	

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) hpcalc.o core

realclean:        clean
	-/bin/rm -f hpcalc 
