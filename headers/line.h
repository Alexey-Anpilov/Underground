#ifndef LINE_H_
#define LINE_H_
#include<iostream>
#include"skip_list.h"
#include"station.h"

class Line{
private:
    bool is_circle = false;

    skip_list<uint, Station*> line;

    void changeTravel(Station* first_st, Station* second_st, uint time);
    
    void renumStations(uint st_num);
public:
    void addStation(uint st_num, uint stream, std::string name, uint time = 0, uint add_time = 0);

    const Station& find(uint st_num);   //поиск станции по номеру

    Station findLeftNeighbor(uint st_num);

    Station findRightNeighbor(uint st_num);

    uint minTime(uint st_num1, uint st_num2);

    void makeCircle(uint time);
};

skip_list<uint, Station*>::Iterator operator+(skip_list<uint, Station*>::Iterator it, int n);

skip_list<uint, Station*>::Iterator operator-(skip_list<uint, Station*>::Iterator it, int n);

#endif