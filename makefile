# MAKEFILE

NAME:=stocktrader
CFLAGS:=-std=c17 -Wall
DFLAGS:=-Og -DDEBUG -D_DEBUG
RFLAGS:=-O3 -DNDEBUG -D_RELEASE

SRC:=src
OBJ:=temp
BIN:=build
DEBUG:=debug
RELEASE:=release
WINDOWS:=windows

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

# Dumb way to get variables specific to target
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) $(DFLAGS)
	ifeq (,$(filter clean,$(MAKECMDGOALS)))
		OBJ:=$(OBJ)/$(DEBUG)
	endif
	ifeq (,$(filter clear,$(MAKECMDGOALS)))
		BIN:=$(BIN)/$(DEBUG)
	endif
endif

ifneq (,$(filter release,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) $(RFLAGS)
	ifeq (,$(filter clean,$(MAKECMDGOALS)))
		OBJ:=$(OBJ)/$(RELEASE)
	endif
	ifeq (,$(filter clear,$(MAKECMDGOALS)))
		BIN:=$(BIN)/$(RELEASE)
	endif
endif

ifneq (,$(filter debugw,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) $(DFLAGS)
	ifeq (,$(filter clean,$(MAKECMDGOALS)))
		OBJ:=$(OBJ)/$(WINDOWS)/$(DEBUG)
	endif
	ifeq (,$(filter clear,$(MAKECMDGOALS)))
		BIN:=$(BIN)/$(WINDOWS)/$(DEBUG)
	endif

	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
endif

ifneq (,$(filter releasew,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) $(RFLAGS)
	ifeq (,$(filter clean,$(MAKECMDGOALS)))
		OBJ:=$(OBJ)/$(WINDOWS)/$(RELEASE)
	endif
	ifeq (,$(filter clear,$(MAKECMDGOALS)))
		BIN:=$(BIN)/$(WINDOWS)/$(RELEASE)
	endif

	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
endif

HEADERS:=$(wildcard $(SRC)/*.h)
SOURCES:=$(wildcard $(SRC)/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))

.PHONY: makefile help clear clean debug release debugw releasew

# Default target simply tells you how to correctly use this makefile
.DEFAULT_GOAL:=help
help:
	@printf "clear: Remove bin files\n\
	clean: Remove temp files\n\
	debug: Make a debug build\n\
	release: Make a release build\n\
	debugw: Make a debug build for windows\n\
	releasew: Make a release build for windows\n"

clear:
	rm -rf $(BIN)/

clean:
	rm -rf $(OBJ)/

# Compile any object files that need to be updated
$(OBJ)/%.o:: $(SRC)/%.c $(HEADERS)
	$(C) $(CFLAGS) -c -o $@ $< $(INCPATH) $(LIBS)

# Link the object files into the binary file
$(BIN)/$(NAME): $(OBJ)/ $(BIN)/ $(OBJECTS)
	$(C) $(CFLAGS) -o $@ $(LIBPATH) $(LIBS) $(OBJECTS)

debug: $(BIN)/$(NAME)
release: $(BIN)/$(NAME)
debugw: $(BIN)/$(NAME)
releasew: $(BIN)/$(NAME)

# Make directories as needed
$(BIN)/: ; mkdir -p $@
$(OBJ)/: ; mkdir -p $@
