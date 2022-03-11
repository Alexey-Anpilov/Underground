#ifndef STATION_H_
#define STATION_H_

#include <string>


class Station{
private:
    uint station_num;    // номер станции
    uint stream;         // пассажиропоток
    std::string name;   // имя станции 

public:
    
    Station(int st_num, int stream, std::string name) // создать станцию с заданными параметрами
        :station_num(st_num),
         stream(stream),
         name(name) {}  


    
    void ChangePassStream(int new_stream);   // изменение пассажиропотока
    
    // получение значений полей

    uint GetNum() const{        
        return station_num;
    }
    
    uint GetStream() const{    
        return stream;
    }

    std::string GetName() const{
        return name;
    }

};

// перегрузка операторов < и == для сравнения по номеру станции

bool operator<(const Station& lhs, const Station& rhs);

bool operator==(const Station& lhs, const Station& rhs);

#endif