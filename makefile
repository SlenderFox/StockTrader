
CC = gcc
CFLAGS = -Wall -O2
OBJECTS = temp/main.o temp/io.o temp/buffer.o

all: stocktrader

stocktrader: $(OBJECTS)
	$(CC) $(CFLAGS) -o build/$@ $?

temp/%.o: src/%.c
	$(CC) $(CFLAGS) -c $? -o $@

.PHONY: clean
clean:
	rm -rf temp/*.o
