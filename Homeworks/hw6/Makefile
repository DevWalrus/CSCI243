#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Oct 27 18:19:52 2021
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

# standard compile flags
#
CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic

# Add the math library in case people want it
#
CLIBFLAGS = -lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	HeapDT.c test_HeapDT.c test_HeapDT2.c
PS_FILES =	
S_FILES =	
H_FILES =	HeapDT.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	HeapDT.o 

#
# Main targets
#

all:	test_HeapDT test_HeapDT2 

test_HeapDT:	test_HeapDT.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_HeapDT test_HeapDT.o $(OBJFILES) $(CLIBFLAGS)

test_HeapDT2:	test_HeapDT2.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_HeapDT2 test_HeapDT2.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

HeapDT.o:	HeapDT.h
test_HeapDT.o:	HeapDT.h
test_HeapDT2.o:	HeapDT.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) test_HeapDT.o test_HeapDT2.o core

realclean:        clean
	-/bin/rm -f test_HeapDT test_HeapDT2 
