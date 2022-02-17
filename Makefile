FLAGS = -Wall -Wextra

all: test


test: station.o test.o
	g++ station.o test.o -o test


station.o: station.cpp station.h 
	g++ -c $(FLAGS) station.cpp


test.o: test.cpp station.h
	g++ -c $(FLAGS) test.cpp

clean:
	rm -rf *.o test