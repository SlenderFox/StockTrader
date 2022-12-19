# General variables
NAME:=stocktrader
CFLAGS:=-std=c17 -Wall
SRC:=src
OBJ:=temp
BIN:=build

# For native comiling
CC:=gcc
INCPATH:=
LIBPATH:=
LIBS:=

# For compiling windows builds on linux
CCW:=x86_64-w64-mingw32-gcc
INCPATHW:=
LIBPATHW:=
LIBSW:=

# Input files
HEADERS:=$(wildcard $(SRC)/*.h)
SOURCES:=$(wildcard $(SRC)/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

# These are targets that do not point to files
.PHONY: all debug release debugw releasew objects clean cleanw

# Default entry point
all: debug

# Make a native debug build
debug: CFLAGS:=$(CFLAGS) -O1
debug: clean
debug: build

# Make a native release build
release: CFLAGS:=$(CFLAGS) -O3
release: clean
release: build

# Make a windows debug build on linux
debugw: CC:=$(CCW)
debugw: INCPATH:=$(INCPATHW)
debugw: LIBPATH:=$(LIBPATHW)
debugw: LIBS:=$(LIBSW)
debugw: debug

# Make a windows release build on linux
releasew: CC:=$(CCW)
releasew: INCPATH:=$(INCPATHW)
releasew: LIBPATH:=$(LIBPATHW)
releasew: LIBS:=$(LIBSW)
releasew: release

build: $(OBJ)/ $(BIN)/ $(BIN)/$(NAME)

# Will build if any file is changed
$(BIN)/$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBPATH) $(LIBS)

# Called when an object file needs to be built
$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCPATH) $(LIBS)

# Make the directory for the object files
$(OBJ)/:
	mkdir $(OBJ)

# Make the directory for the binary files
$(BIN)/:
	mkdir $(BIN)

# Only compiles the objects
objects: $(OBJECTS)

# Removing temporary files on linux
clean:
	rm -f $(OBJ)/*

# Removing temporary files on windows
cleanw:
	del $(OBJ)/
