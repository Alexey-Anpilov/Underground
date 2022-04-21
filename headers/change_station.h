#ifndef CHANGE_STATION_H_
#define CHANGE_STATION_H_
#include"station.h"
#include"change.h"


class ChangeStation:public Station{
private:    
    std::vector<Change> changes;    //набор пересадок на другие линии
public:
    ChangeStation(int st_num, int stream, std::string name)
        :Station(st_num, stream, name) {} 
    
    ChangeStation(const Station& st)
        :Station(st) {}

    virtual void addChange(const Change& ch) override;   //добавление пересадки
    
    virtual std::vector<Change> getChanges() const override{     //получение набора пересадок
        return changes;
    }

    virtual bool isChangeStation() const override{
        return true;
    }
};

#endif