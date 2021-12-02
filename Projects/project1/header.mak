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
