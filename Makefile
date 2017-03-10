# Directories
OBJDIR ?= bld
SRCDIR = src

# Compiler and compilation flags
CC = gcc

# Adding recommended warnings
CFLAGS+= -Wall -Wextra -Wunreachable-code
# Abusing warning switches
CFLAGS+= -Wbad-function-cast -Wstrict-prototypes -Wdeclaration-after-statement
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces -Winline
CFLAGS+= -Wno-missing-field-initializers

# Executables
EXEC = $(OBJDIR)/proj


# General rules
all: $(EXEC)

$(EXEC): $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $^ -o $@

debug: CFLAGS += -g -DDEBUG
debug: all

tests: debug
	tests/runtests.sh -e $(EXEC)

valgrind: debug
	tests/runtests.sh -e $(EXEC) --use-valgrind

clean:
	rm -rf $(EXEC) $(OBJDIR)/*.o $(OBJDIR)/*.dSYM

.PHONY: all clean debug test valgrind
