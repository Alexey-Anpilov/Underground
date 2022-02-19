FLAGS = -Wall -Wextra

all: test


test: station.o test.o line.o
	g++ station.o test.o line.o -o test


station.o: station.cpp station.h 
	g++ -c $(FLAGS) station.cpp


test.o: test.cpp station.h line.h travel.h
	g++ -c $(FLAGS) test.cpp

line.o: line.cpp line.h travel.h
	g++ -c $(FLAGS) line.cpp


clean:
	rm -rf *.o test