# Makefile :)

# Useless ↓
#vpath %.c src
#vpath %.h src
#vpath %.o temp

NAME := stocktrader
W =

CC := gcc
INCPATH :=
LIBPATH :=

CCW := x86_64-w64-mingw32-gcc
INCPATHW := -I/usr/x86_64-w64-mingw32/include -I/usr/include
LIBPATHW := -L/usr/x86_64-w64-mingw32/lib -L/usr/lib

CFLAGS := -std=gnu17 -O2 -Wall
LIBS := #-lm -lncurses

HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.c)
# Convert each source file into a potential object file
OBJECTS := $(patsubst src/%.c, temp/%.o, $(SOURCES))

LINK = $(CC$(W)) $(CFLAGS) -o build/$(NAME) $(OBJECTS) $(LIBPATH$(W)) $(LIBS)
COMPILE = $(CC$(W)) $(CFLAGS) -c $< -o $@ $(INCPATH$(W)) $(LIBS)

# These are functions not targets
.PHONY: all objects clean build_sensitive build_sensitive_w

# Defaul entry point
all: build_sensitive

objects: $(OBJECTS)

# Will build if any file is changed
build_sensitive: $(OBJECTS) $(SOURCES) $(HEADERS)
	$(LINK)

#build: src/*.c src/*.h
#	$(CC) $(CFLAGS) -o build/$@

# Called when an object file needs to be built
temp/%.o: src/%.c $(HEADERS)
	$(COMPILE)

clean:
	rm -f temp/*.o
