#ifndef TRAVEL_H_
#define TRAVEL_H_

#include"station.h"

class Travel{
private:
    uint time;
    Station* first_st = nullptr;
    Station* second_st = nullptr;
public:
    Travel(uint time):time(time) {}
    void SetFirst(Station* st){
        first_st = st;
    }
    
    void SetSecond(Station* st){
        second_st = st;
    }

    void SetTime(uint t){
        time = t;
    }
    
    Station GetFirstStation(){
        return *first_st;
    }


    Station GetSecondStation(){
        return *second_st;
    }

    uint GetTime()const {
        return time;
    }
};

#endif