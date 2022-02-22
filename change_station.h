#ifndef CHANGE_STATION_H_
#define CHANGE_STATION_H_
#include <vector>
#include "change.h"
#include "station.h"

class ChangeStation : public Station{
private:
    std::vector<Change> change_station;
public:
    ChangeStation(uint st_num, uint stream, std::string name, std::vector<Change> change_station)
         :Station(st_num, stream, name), change_station(change_station) {}
    
    // дописать функцию выдающую change_station
};

#endif