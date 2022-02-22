#ifndef CHANGE_H_
#define CHANGE_H_
#include"station.h"

class Change{
private:
    uint time;   //время на пересадку(мин)
    uint stream;    //средний пассажиропоток(чел/час)
    std::pair<Station, Station> change; //Пересадка
public:
    Change(uint time, uint stream, std::pair<Station, Station> change)
        :time(time),
         stream(stream),
         change(change) {}
    
    std::pair<Station, Station> GetChange() const{
        return change;
    }

    uint GetTime() const{
        return time;
    }

    uint GetStream() const{
        return stream;
    }
};

#endif