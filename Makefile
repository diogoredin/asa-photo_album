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

# General rules
all: CFLAGS += -O3
all: proj1

debug: CFLAGS += -g -O0 -DDEBUG
debug: proj1

# Specific rules
proj1: $(EXEC_PROJ1)
proj1pp: $(EXEC_PROJ1PP)

$(EXEC_PROJ1): $(SRCDIR)/proj1.c
	$(CC) $(CCFLAGS) $^ -o $@

$(EXEC_PROJ1PP): $(SRCDIR)/proj1.cpp
	$(CXX) $(CXFLAGS) $^ -o $@

tests: debug
	tests/runtests.sh -e $(EXEC)

valgrind: debug
	tests/runtests.sh -e $(EXEC) --use-valgrind

clean:
	rm -rf $(EXECS) $(OBJDIR)/*.o $(OBJDIR)/*.dSYM

.PHONY: all clean debug test valgrind
