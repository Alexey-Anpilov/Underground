INCLUDEDIR=headers 
CC=g++
CPPFLAGS=-std=c++17 -g -Wall -Wextra
LDFLAGS=
SOURCES=src/change_station.cpp src/line.cpp src/station.cpp test/test.cpp
OBJDIR=build
OBJECTS=$(SOURCES:%.cpp=$(OBJDIR)/%.o)
EXECUTABLE=underground

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -c $(CPPFLAGS) -I$(INCLUDEDIR) $< -o $@

clean:
	rm -f underground
	rm -rf build