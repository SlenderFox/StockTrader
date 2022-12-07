build: temp/main.o temp/io.o temp/buffer.o
	g++ -o build/stocktrader temp/main.o temp/io.o temp/buffer.o

temp/main.o: src/main.cpp src/io.hpp src/buffer.hpp src/typeDefines.hpp
	g++ -c src/main.cpp -o temp/main.o

temp/io.o: src/io.hpp src/buffer.hpp src/typeDefines.hpp
	g++ -c src/io.cpp -o temp/io.o

temp/buffer.o: src/buffer.hpp src/typeDefines.hpp
	g++ -c src/buffer.cpp -o temp/buffer.o

clean:
	rm -rf temp/
