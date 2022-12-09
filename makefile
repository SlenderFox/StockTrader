# Makefile :)

# Useless ↓
#vpath %.c src
#vpath %.h src
#vpath %.o temp

NAME := stocktrader
CC := gcc
CFLAGS := -std=gnu17 -O2 -Wall
HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.c)
# Convert each source file into a potential object file
OBJECTS := $(patsubst src/%.c, temp/%.o, $(SOURCES))

# These are functions not targets
.PHONY: all clean build_sensitive
.INTERMEDIATE: temp/%.o

# Defaul entry point
all: build_sensitive

# Will build if any file is changed
build_sensitive: $(OBJECTS) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o build/$(NAME) $(OBJECTS)

#build: src/*.c src/*.h
#	$(CC) $(CFLAGS) -o build/$@

# Called when an object file needs to be built
temp/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f temp/*.o
