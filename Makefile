# Directories
SRCDIR = src
OBJDIR = bld

# Compilers
CC  = gcc
CXX = g++

# Shared compilation flags
CFLAGS = -ansi -pedantic -Wall -Wextra -Wunreachable-code
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces -Winline
CFLAGS+= -Wno-missing-field-initializers

# Specific flags
CCFLAGS = $(CFLAGS) -std=c89
CXFLAGS = $(CFLAGS)

# Executables
EXEC_PROJ1   = $(OBJDIR)/proj1
EXEC_PROJ1PP = $(OBJDIR)/proj1pp
EXECS = $(EXEC_PROJ1) $(EXEC_PROJ1PP)

# General rules (point to main focus files)
all: CFLAGS += -O3
all: proj1

debug: CFLAGS += -g -O0 -DDEBUG
debug: proj1

clean:
	rm -rf $(EXECS) $(OBJDIR)/*.o $(OBJDIR)/*.dSYM

# Specific rules
proj1: $(EXEC_PROJ1)
proj1pp: $(EXEC_PROJ1PP)

# Compilation rules
$(EXEC_PROJ1): $(SRCDIR)/proj1.c
	$(CC) $(CCFLAGS) $^ -o $@

$(EXEC_PROJ1PP): $(SRCDIR)/proj1.cpp
	$(CXX) $(CXFLAGS) $^ -o $@


.PHONY: all clean debug test valgrind
