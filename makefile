# Makefile :)

# Useless ↓
#vpath %.c src
#vpath %.h src
#vpath %.o temp

NAME:=stocktrader
W=

CC:=g++
CFLAGS:=-std=c++20 -O2 -Wall

INCPATH:=
LIBPATH:=

CCW:=x86_64-w64-mingw32-g++
INCPATHW:=
LIBPATHW:=

LIBS:=

HEADERS:=$(wildcard src/cpp/*.hpp)
SOURCES:=$(wildcard src/cpp/*.cpp)
# Convert each source file into a potential object file
OBJECTS:=$(patsubst src/cpp/%.cpp, temp/%.o, $(SOURCES))

LINK=$(CC$(W)) $(CFLAGS) -o build/$(NAME) $(OBJECTS) $(LIBPATH$(W)) $(LIBS)
COMPILE=$(CC$(W)) $(CFLAGS) -c $< -o $@ $(INCPATH$(W)) $(LIBS)

# These are functions not targets
.PHONY: entry all objects clean build_sensitive

# Defaul entry point
entry: build_sensitive

# Runs clean before building
all: clean build_sensitive

# Only compiles the objects
objects: $(OBJECTS)

# Will build if any file is changed
build_sensitive: $(OBJECTS) $(SOURCES) $(HEADERS)
	$(LINK)

# Called when an object file needs to be built
temp/%.o: src/cpp/%.cpp $(HEADERS)
	$(COMPILE)

clean:
	rm -f temp/*.o
