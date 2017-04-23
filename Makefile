# Directories
SRCDIR = src
OBJDIR = bld

# Compilers
CC  ?= gcc
CXX ?= g++

# Shared compilation flags
CFLAGS = -ansi -pedantic -Wall -Wextra -Wunreachable-code
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces -Winline
CFLAGS+= -Wno-missing-field-initializers

BUILD ?= release
ifeq ($(BUILD), debug)
	CFLAGS += -g -O0 -DDEBUG
else
	CFLAGS += -O3
endif

# Specific flags
CCFLAGS = $(CFLAGS) -std=c89
CXFLAGS = $(CFLAGS)

# Executables
EXEC_PROJ1   = $(OBJDIR)/proj1
EXEC_PROJ1PP = $(OBJDIR)/proj1pp
EXEC_PROJ2   = $(OBJDIR)/proj2
EXEC_PROJ2PP = $(OBJDIR)/proj2pp
EXECS = $(EXEC_PROJ1) $(EXEC_PROJ1PP) $(EXEC_PROJ2) $(EXEC_PROJ2PP)


# General rules (point to main focus files)
all: proj2

clean:
	rm -rf $(EXECS) $(OBJDIR)/*.o $(OBJDIR)/*.dSYM

# Compilation rules
proj1: $(SRCDIR)/proj1.c
	$(CC) $(CCFLAGS) $^ -o $@
proj1pp: $(SRCDIR)/proj1.cpp
	$(CXX) $(CXFLAGS) $^ -o $@

proj2: $(SRCDIR)/proj2.c
	$(CC) $(CCFLAGS) $^ -o $@
proj2pp: $(SRCDIR)/proj2.cpp
	$(CXX) $(CXFLAGS) $^ -o $@


.PHONY: all clean
