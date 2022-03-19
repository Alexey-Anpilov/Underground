#ifndef STATION_H_
#define STATION_H_

#include<string>
#include"change.h"
#include<vector>

class Station{
private:
    uint station_num;    // номер станции
    uint stream;         // пассажиропоток
    std::string name;   // имя станции 

public:
    
    Station(int st_num, int stream, const std::string& name) // создать станцию с заданными параметрами
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

    const std::string& GetName() const{
        return name;
    }

    void SetStNum(uint new_stnum){      //изменение номера станции
        station_num = new_stnum;
    }

    virtual std::vector<Change> GetChanges() const{     //будет проверяться, что возвращаемый вектор пустой => по указателю лежит Station 
        return {};
    }

    virtual ~Station() {}   //виртуальный декструктор для корректной очистки для классов-наследников
};

// перегрузка операторов < и == для сравнения по номеру станции

bool operator<(const Station& lhs, const Station& rhs);

bool operator==(const Station& lhs, const Station& rhs);

#endif