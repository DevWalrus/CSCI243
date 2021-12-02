#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Oct  6 12:06:15 2021
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
# Define any additional compilation flags you want to use while testing
# (e.g., -DDEBUG to predefine the CPP macro symbol 'DEBUG', which could
# be used to conditionally compile in debugging code).
#
OPTS = -DDEBUG
#
# Note the use of -Werror, which causes warning messages to be considered
# fatal compilation errors.
#
CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic -Werror $(OPTS)
#
# Link to public hashtable archive
#
CLIBFLAGS = -L/home/course/csci243/pub/projects/01 -ltable -lm 

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	amici.c errors.c person.c process.c test_table.c
PS_FILES =	
S_FILES =	
H_FILES =	amici.h errors.h hash.h person.h process.h table.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	errors.o person.o process.o 

#
# Main targets
#

all:	amici test_table 

amici:	amici.o $(OBJFILES)
	$(CC) $(CFLAGS) -o amici amici.o $(OBJFILES) $(CLIBFLAGS)

test_table:	test_table.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_table test_table.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

amici.o:	hash.h person.h process.h table.h
errors.o:	
person.o:	person.h
process.o:	errors.h person.h
test_table.o:	hash.h table.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) amici.o test_table.o core

realclean:        clean
	-/bin/rm -f amici test_table 
