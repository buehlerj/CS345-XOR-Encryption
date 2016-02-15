CXXFLAGS = -c -g -Wall -I.
all: a1

a1: main.o Block.o Stream.o
	g++ -o a1 main.o Block.o Stream.o

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp
BLock.o: Block.h Block.cpp
	g++ $(CXXFLAGS) Block.h Block.cpp
Stream.o: Stream.h Stream.cpp
	g++ $(CXXFLAGS) Stream.h Stream.cpp

clean:
	-rm -f a1 *.o *.gch *.txt~
tar:
	tar -cf A1.tar *.cpp *.h *.txt Makefile
