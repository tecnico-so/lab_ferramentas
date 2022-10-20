# Makefile
# Sistemas Operativos, DEI/IST/ULisboa 2022-23
#
# This makefile should be run from the *root*

# Set CC (C compiler) and LD (loader/linker) if they are not already set (as environment variables)
CC ?= gcc
LD ?= gcc

# space separated list of directories with header files
INCLUDE_DIRS := include
# this creates a space separated list of -I<dir> where <dir> is each of the values in INCLUDE_DIRS
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

# find all source files
SOURCES  := $(wildcard */*.c)

# find all header files
HEADERS  := $(wildcard */*.h)

# create list of the target object files, by replacing the `.c` extensions with `.o`
OBJECTS  := $(SOURCES:.c=.o)

# target executable
TARGET_EXECS := bin/test

# VPATH is a variable used by Makefile which finds *sources* and makes them available throughout the codebase
# vpath %.h <DIR> tells make to look for header files in <DIR>
vpath # clears VPATH
vpath %.h $(INCLUDE_DIRS)

CFLAGS = -std=c17 -D_POSIX_C_SOURCE=200809L
CFLAGS += $(INCLUDES)

# make warnings have colors
CFLAGS += -fdiagnostics-color=always
# Warnings
CFLAGS += -Wall -Werror -Wextra -Wcast-align -Wconversion -Wfloat-equal -Wformat=2 -Wnull-dereference -Wshadow -Wsign-conversion -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused
# Warning suppressions
CFLAGS += -Wno-sign-compare

# optional debug symbols: run make DEBUG=no to deactivate them
# debug symbols are required to use debugging infrastructure (eg: gdb, valgrind, better error messages in sanitizers)
ifneq ($(strip $(DEBUG)), no)
  CFLAGS += -g
endif

# optional O3 optimization symbols: run make OPTIM=no to deactivate them
ifeq ($(strip $(OPTIM)), no)
  CFLAGS += -O0
else
  CFLAGS += -O3
endif

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean depend fmt

all: $(TARGET_EXECS)

# The following target can be used to invoke clang-format on all the source and header
# files. clang-format is a tool to format the source code based on the style specified
# in the file '.clang-format'.
# More info available here: https://clang.llvm.org/docs/ClangFormat.html

# The $^ keyword is used in Makefile to refer to the right part of the ":" in the
# enclosing rule. See https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

fmt: $(SOURCES) $(HEADERS)
	clang-format -i $^



# Note the lack of a rule.
# make uses a set of default rules, one of which compiles C binaries
# the CC, LD, CFLAGS and LDFLAGS are used in this rule

# The $@ keyword is used in Makefile to refer to the left part of the ":" in the
# enclosing rule. See https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

bin/test: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS) $(TARGET_EXECS)


# This generates a dependency file, with some default dependencies gathered from the include tree
# The dependencies are gathered in the file autodep. You can find an example illustrating this GCC feature, without Makefile, at this URL: https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/options/MM
# Run `make depend` whenever you add new includes in your files
depend : $(SOURCES)
	$(CC) $(INCLUDES) -MM $^ > autodep
