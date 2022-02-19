#ifndef STATION_H_
#define STATION_H_

#include <string>


class Station{
private:
    uint st_num;    // номер станции
    uint stream;         // средний пассажиропоток(чел/час)
    std::string name;   // имя станции 

public:
    
    Station(uint st_num, uint stream, std::string name) // создать станцию с заданными параметрами
        :st_num(st_num),
         stream(stream),
         name(name) {}  


    
    void ChangePassStream(uint new_stream);   // изменение пассажиропотока

    // перегрузка операторов < и == для сравнения по номеру станции

    
    bool operator<(const Station& st); 
    
    bool operator==(const Station& st);
 
    // получение значений полей

    uint GetNum() const{        
        return st_num;
    }
    
    uint GetStream() const{    
        return stream;
    }

    std::string GetName() const{
        return name;
    }

};

#endif