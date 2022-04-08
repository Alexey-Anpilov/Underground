#ifndef STATION_H_
#define STATION_H_

#include<string>
#include"change.h"
#include<vector>
#include"travel.h"


class Station{
private:
    uint station_num;    // номер станции
    uint stream;         // пассажиропоток
    std::string name;   // имя станции 
    Travel forward;
    Travel back;
public:
    Station(int st_num, int stream, const std::string& name) // создать станцию с заданными параметрами
        :station_num(st_num),
         stream(stream),
         name(name) {}  


    void changePassStream(int new_stream);   // изменение пассажиропотока
    

    uint getNum() const{            //получение номера станции
        return station_num;
    }
    
    uint getStream() const{         //получение пассажиропотока станции 
        return stream;
    }

    const std::string& getName() const{    //получение имени станции
        return name;
    }

    void setStNum(uint new_stnum){      //изменение номера станции
        station_num = new_stnum;
    }

    void setTravelFor(uint time, Station* st);

    void setTravelBack(uint time, Station* st);

    uint travelForwardTime() const;

    Station travelForward() const{
        return *forward.second_st;
    }

    Station travelBack() const{
        return *back.second_st;
    }
    
    uint travelBackTime() const;

    virtual std::vector<Change> getChanges() const{     //будет проверяться, что возвращаемый вектор пустой => по указателю лежит Station 
        return {};
    }

    virtual ~Station() {}   //виртуальный декструктор для корректной очистки для классов-наследников
};

// перегрузка операторов < и == для сравнения по номеру станции

bool operator<(const Station& lhs, const Station& rhs);

bool operator==(const Station& lhs, const Station& rhs);

#endif