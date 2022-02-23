FLAGS = -Wall -Wextra

all: test


test: station.o test.o line.o
	g++ station.o test.o line.o -o test


station.o: station.cpp station.h 
	g++ -c $(FLAGS) station.cpp


test.o: test.cpp station.h
	g++ -c $(FLAGS) test.cpp

line.o: line.h travel.h
	g++ -c $(FLAGS) line.cpp

clean:
	rm -rf *.o test