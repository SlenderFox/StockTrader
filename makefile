NAME:=stocktrader
CFLAGS:=-std=c17 -Wall
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
	CFLAGS:=$(CFLAGS) -O1 -DDEBUG
	OBJ:=$(OBJ)/$(DEBUG)
	BIN:=$(BIN)/$(DEBUG)
endif

ifneq (,$(filter release,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) -O3 -DNDEBUG
	OBJ:=$(OBJ)/$(RELEASE)
	BIN:=$(BIN)/$(RELEASE)
endif

ifneq (,$(filter debugw,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) -O1 -DDEBUG
	OBJ:=$(WINDOWS)/$(OBJ)/$(DEBUG)
	BIN:=$(WINDOWS)/$(BIN)/$(DEBUG)

	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
endif

ifneq (,$(filter releasew,$(MAKECMDGOALS)))
	CFLAGS:=$(CFLAGS) -O3 -DNDEBUG
	OBJ:=$(WINDOWS)/$(OBJ)/$(RELEASE)
	BIN:=$(WINDOWS)/$(BIN)/$(RELEASE)

	C:=$(CW)
	INCPATH:=$(INCPATHW)
	LIBPATH:=$(LIBPATHW)
	LIBS:=$(LIBSW)
endif

HEADERS:=$(wildcard $(SRC)/*.h)
SOURCES:=$(wildcard $(SRC)/*.c)
OBJECTS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))

.PHONY: makefile all clean build debug release debugw releasew

# Dumb way to get default target working
.DEFAULT_GOAL:=all
all: CFLAGS:=$(CFLAGS) -O1 -DDEBUG
all: OBJ:=$(OBJ)/$(DEBUG)
all: BIN:=$(BIN)/$(DEBUG)
all: build

clean:
	rm -rf $(OBJ)/
	rm -rf $(BIN)/
	rm -rf $(WINDOWS)/

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
