#ifndef CHANGE_STATION_H_
#define CHANGE_STATION_H_
#include"station.h"
#include"change.h"

class ChangeStation:public Station{
private:
    uint station_num;    // номер станции
    uint stream;         // пассажиропоток
    std::string name;   // имя станции 
    
    std::vector<Change> changes;
public:
    ChangeStation(int st_num, int stream, std::string name)
        :Station(st_num, stream, name) {} 
    
    std::vector<Change> GetChanges() const{
        return changes;
    }
};

#endif