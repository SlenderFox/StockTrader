build: temp/main.o temp/io.o temp/buffer.o
	gcc -o build/stocktrader temp/main.o temp/io.o temp/buffer.o

temp/main.o: src/main.c src/io.h src/buffer.h src/typedefines.h
	gcc -c src/main.c -o temp/main.o

temp/io.o: src/io.c src/io.h src/buffer.h src/typedefines.h
	gcc -c src/io.c -o temp/io.o

temp/buffer.o: src/buffer.c src/buffer.h src/typedefines.h
	gcc -c src/buffer.c -o temp/buffer.o

clean:
	rm -rf temp/**
