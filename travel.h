#ifndef TRAVEL_H_
#define TRAVEL_H_

#include "station.h"


class Travel{
private:
    std::pair<Station&, Station&> travel;
    uint time;
public:
    Travel(Station& st1, Station& st2, uint time)   
        :travel(st1, st2),
         time(time) {}

    uint GetTime() const{
        return time;
    }

    Station& GetFirstStation() const{
        return travel.first;
    }     

    Station& GetSecondStation() const{
        return travel.second;
    }
};



#endif