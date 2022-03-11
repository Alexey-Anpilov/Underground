#ifndef TRAVEL_H_
#define TRAVEL_H_

#include"station.h"
#include<memory.h>


class Travel{
private:
    uint time;                      //время прогона(мин)
    Station* first_st = nullptr;    //указатель на первую станцию
    Station* second_st = nullptr;   //указатель на вторую станцию
    friend class Line;
public:
    Travel(uint time):time(time) {}
    
    //получение значений полей класса

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