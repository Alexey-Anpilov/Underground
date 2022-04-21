#ifndef LINE_H_
#define LINE_H_
#include<iostream>
#include"skip_list.h"
#include"station.h"
#include<map>
#include"change_station.h"

class Line{
private:
    bool is_circle = false;

    std::map<std::string, uint> stations;

    skip_list<uint, Station*> line;

    void changeTravel(Station* first_st, Station* second_st, uint time);
    
    void addSt(Station* st, uint time, uint add_time);

    void renumStations(uint st_num);
    
    
    friend class Underground;
public:
    Line(const Line& l);
    
    Line();

    void addStation(uint st_num, uint stream, std::string name, uint time = 0, uint add_time = 0);

    void addChangeStation(uint st_num, uint stream, std::string name, uint time = 0, uint add_time = 0);

    const Station& find_t(uint st_num);   //поиск станции по номеру

    Station* find_p(uint st_num){
        auto it = line.find(st_num);
        return *it;
    }

    void addChange(std::string name, Change ch);

    skip_list<uint, Station*>::Iterator find(uint st_num);

    Station findLeftNeighbor(uint st_num);

    Station findRightNeighbor(uint st_num);

    uint minTime(uint st_num1, uint st_num2);

    uint onLine(std::string name) const;

    void makeCircle(uint time);

    Line& operator=(const Line& l);

    ~Line();
};

skip_list<uint, Station*>::Iterator operator+(skip_list<uint, Station*>::Iterator it, int n);

skip_list<uint, Station*>::Iterator operator-(skip_list<uint, Station*>::Iterator it, int n);

#endif