# makefile :)

NAME:=stocktrader
CFLAGS:=-std=c17 -O2 -Wall

# For native comiling
CC:=gcc
INCPATH:=
LIBPATH:=
LIBS:=

# For compiling windows builds on linux, set to W to activate
W=
CCW:=x86_64-w64-mingw32-gcc
INCPATHW:=
LIBPATHW:=
LIBSW:=

# Precomputing the result of above
CCR=$(CC$(W))
INCPATHR=$(INCPATH$(W))
LIBPATHR=$(LIBPATH$(W))
LIBSR=$(LIBS$(W))

# Input files
HEADERS:=$(wildcard src/*.h)
SOURCES:=$(wildcard src/*.c)
# Convert each source file into a potential object file
OBJECTS:=$(patsubst src/%.c, temp/%.o, $(SOURCES))

# The command used for linking
LINK=$(CCR) $(CFLAGS) -o build/$(NAME) $(OBJECTS) $(LIBPATHR) $(LIBSR)
# The command using for compiling and assembling
COMPILE=$(CCR) $(CFLAGS) -c $< -o $@ $(INCPATHR) $(LIBSR)

# These are targets that do not point to files
.PHONY: entry all objects clean build_sensitive

# Default entry point
entry: build_sensitive

# Runs clean before building
all: clean build_sensitive

# Only compiles the objects
objects: $(OBJECTS)

# Will build if any file is changed
build_sensitive: $(OBJECTS) #$(SOURCES) $(HEADERS)
	$(LINK)

# Called when an object file needs to be built
temp/%.o: src/%.c $(HEADERS)
	$(COMPILE)

clean:
	rm -f temp/*.o
