NAME:=stocktrader
CFLAGS:=-std=c17 -Wall
SRC:=src
OBJ:=temp
BIN:=build
DEBUG:=debug
RELEASE:=release
WINDOWS:=win

# For native comiling
C:=gcc
INCPATH:=
LIBPATH:=
LIBS:=

# For compiling windows builds on linux
CW:=x86_64-w64-mingw32-gcc
INCPATHW:=
LIBPATHW:=
LIBSW:=

ISDEBUG:=$(filter debug,$(MAKECMDGOALS))
ISRELEASE:=$(filter release,$(MAKECMDGOALS))
ISDEBUGW:=$(filter debugw,$(MAKECMDGOALS))
ISRELEASEW:=$(filter releasew,$(MAKECMDGOALS))

ifeq (debug,$(ISDEBUG))
	CFLAGS:=$(CFLAGS) -O1 -DDEBUG
	OBJ:=$(OBJ)/$(DEBUG)
	BIN:=$(BIN)/$(DEBUG)
endif

ifeq (release,$(ISRELEASE))
	CFLAGS:=$(CFLAGS) -O3 -DNDEBUG
	OBJ:=$(OBJ)/$(RELEASE)
	BIN:=$(BIN)/$(RELEASE)
endif

ifeq (debugw,$(ISDEBUGW))
	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
	OBJ:=$(OBJ)/$(WINDOWS)
	BIN:=$(BIN)/$(WINDOWS)

	CFLAGS:=$(CFLAGS) -O1 -DDEBUG
	OBJ:=$(OBJ)/$(DEBUG)
	BIN:=$(BIN)/$(DEBUG)
endif

ifeq (releasew,$(ISRELEASEW))
	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
	OBJ:=$(OBJ)/$(WINDOWS)
	BIN:=$(BIN)/$(WINDOWS)

	CFLAGS:=$(CFLAGS) -O3 -DNDEBUG
	OBJ:=$(OBJ)/$(RELEASE)
	BIN:=$(BIN)/$(RELEASE)
endif

HEADERS:=$(wildcard $(SRC)/*.h)
SOURCES:=$(wildcard $(SRC)/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))

.PHONY: makefile clean build debug release debugw releasew

.DEFAULT_GOAL:=debug

clean:
	rm -rf $(OBJ)/
	rm -rf $(BIN)/

# Make any needed directories (bad)
%/: ; mkdir -p $@

# Link the object files into the binary file
$(BIN)/$(NAME): $(OBJECTS)
	$(C) $(CFLAGS) $(OBJECTS) -o $@ $(LIBPATH) $(LIBS)

# Compile any object files that need to be updated
$(OBJ)/%.o:: $(SRC)/%.c $(HEADERS)
	$(C) $(CFLAGS) -c $< -o $@ $(INCPATH) $(LIBS)

build: $(OBJ)/ $(BIN)/ $(BIN)/$(NAME)

debug: build
release: build
debugw: build
releasew: build
