#ifndef CHANGE_H_
#define CHANGE_H_
#include"skip_list.h"


class Station;

class Change{
private:
    uint time;                  //время(мин) на пересадку
    uint stream;                //средний пассажиропоток на пересадке
    Station* first_st;
    Station* second_st;

public: 
    Change(){
        time = 0;
        stream = 0;
        first_st = nullptr;
        second_st = nullptr;
    }

    Change(uint time, uint stream, Station* first_st, Station* second_st)
        :time(time), 
         stream(stream),
         first_st(first_st),
         second_st(second_st) {}

    Station* change() const{
        return second_st;
    }

    Station* stay() const{
        return first_st;
    }
    
    //получение значений полей
    uint timeToChange() const{
        return time;
    }

    uint getStream() const{
        return stream;
    }
};

#endif