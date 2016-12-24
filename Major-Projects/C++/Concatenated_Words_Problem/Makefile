CC=g++

CFLAGS=-c -std=c++0x -Wno-write-strings

all: concatenated

concatenated: main.o concatenated.o
	$(CC) main.o concatenated.o -o concatenated

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

concatenated.o: concatenated.cpp
	$(CC) $(CFLAGS) concatenated.cpp

clean:
	rm *o concatenated





