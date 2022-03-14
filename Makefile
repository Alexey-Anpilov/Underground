FLAGS = -Wall -Wextra

all: test


test: test.o line.o station.o
	g++ station.o test.o line.o -o test

station.o: station.cpp station.h
	g++ -c $(FLAGS) station.cpp
	
test.o: test.cpp
	g++ -c $(FLAGS) test.cpp

line.o: line.cpp line.h travel.h station.h node.h
	g++ -c $(FLAGS) line.cpp

clean:
	rm -rf *.o test line