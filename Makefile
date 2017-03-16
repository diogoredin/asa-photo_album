# Directories
OBJDIR ?= bld
SRCDIR = src

# Compiler and compilation flags
CC = gcc

# Adding recommended warnings
CFLAGS+= -ansi -pedantic -std=c89 -Wall -Wextra -Wunreachable-code
# Abusing warning switches
CFLAGS+= -Wbad-function-cast -Wstrict-prototypes -Wdeclaration-after-statement
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces -Winline
CFLAGS+= -Wno-missing-field-initializers

# Executables
EXEC = $(OBJDIR)/proj1

# General rules
all: CFLAGS += -O3
all: $(EXEC)

$(EXEC): $(SRCDIR)/proj1.c
	$(CC) $(CFLAGS) $^ -o $@

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(EXEC)

tests: debug
	tests/runtests.sh -e $(EXEC)

valgrind: debug
	tests/runtests.sh -e $(EXEC) --use-valgrind

clean:
	rm -rf $(EXEC) $(OBJDIR)/*.o $(OBJDIR)/*.dSYM

.PHONY: all clean debug test valgrind
