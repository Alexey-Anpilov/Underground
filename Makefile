FLAGS = -Wall -Wextra

all: test


test: test.o line.o station.o change_station.o node.o
	g++ station.o test.o line.o change_station.o node.o -o test

station.o: station.cpp station.h
	g++ -c $(FLAGS) station.cpp

change_station.o: change_station.h station.h change_station.cpp station.cpp
	g++ -c $(FLAGS) change_station.cpp

test.o: test.cpp
	g++ -c $(FLAGS) test.cpp

line.o: line.cpp line.h travel.h station.h node.h
	g++ -c $(FLAGS) line.cpp

node.o: node.h
	g++ -c $(FLAGS) node.cpp

clean:
	rm -rf *.o test line