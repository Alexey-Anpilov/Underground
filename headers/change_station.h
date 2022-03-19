#ifndef CHANGE_STATION_H_
#define CHANGE_STATION_H_
#include"station.h"
#include"change.h"
#include<vector>

class ChangeStation:public Station{
private:    
    std::vector<Change> changes;    //набор пересадок на другие линии
public:
    ChangeStation(int st_num, int stream, std::string name)
        :Station(st_num, stream, name) {} 
    
    void AddChange(const Change& ch);   //добавление пересадки
    
    virtual std::vector<Change> GetChanges() const override{     //получение набора пересадок
        return changes;
    }
};

#endif