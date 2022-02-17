#ifndef STATION_H_
#define STATION_H_

#include <string>


class Station{
private:
    int station_num;    // номер станции
    int stream;         // пассажиропоток
    std::string name;   // имя станции 

public:
    
    Station(int st_num, int stream, std::string name) // создать станцию с заданными параметрами
        :station_num(st_num),
         stream(stream),
         name(name) {}  


    
    bool ChangePassStream(int new_stream);   // изменение пассажиропотока

    // перегрузка операторов < и == для сравнения по номеру станции

    
    bool operator<(const Station& st); 
    
    bool operator==(const Station& st);
 
    // получение значений полей

    int GetNum() const{        
        return station_num;
    }
    
    int GetStream() const{    
        return stream;
    }

    std::string GetName() const{
        return name;
    }

};

#endif