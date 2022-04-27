#include"line.h"

void Line::changeTravel(Station* first_st, Station* second_st, uint time){
    first_st->setTravelFor(time, second_st);
    if(second_st != nullptr){
        second_st->setTravelBack(time, first_st);
    }
}

void Line::renumStations(uint st_num){
    auto it = line.find(st_num);
    for(; it != line.end(); ++it){
        it.getNode()->key++;
        (*it)->setStNum(it.getNode()->key);
    }
    it.getNode()->key++;
    (*it)->setStNum(it.getNode()->key);
}

void Line::addSt(Station* st, uint time, uint add_time){
    uint st_num = st->getNum();
    stations[st->getName()] = st_num;
    if (st_num < line.size()){
        renumStations(st_num);
    }
    auto it = line.add(st_num, st);
    if(is_circle){
        if(it == line.begin()){
            it.getNode()->previous = line.end().getNode();
            line.end().getNode()->next = it.getNode();
        }
        if (it == line.end()){
            it.getNode()->next = line.begin().getNode();
            line.begin().getNode()->previous = it.getNode();
        }
        changeTravel(*(it - 1), *it, time);
        changeTravel(*it, *(it + 1), add_time);
        return;
    }
    if (it != line.begin()){
        changeTravel(*(it - 1), *it, time);
    }
    if(it != line.end()){
        changeTravel(*it, *(it + 1), add_time);
    }
}


Line::Line(const Line& l){
    stations = l.stations;
    line = l.line;
    is_circle = l.is_circle;
}

Line::Line(){}

void Line::clear(){
    auto it = line.begin();
    for(; it != line.end(); ++it){
        delete it.getNode()->data;
    }
    delete it.getNode()->data;
}



void Line::addStation(uint st_num, uint stream, std::string name, uint time, uint add_time){
    Station* st = new Station(st_num, stream, name);
    addSt(st, time, add_time);
}

void Line::addChangeStation(uint st_num, uint stream, std::string name, uint time, uint add_time){
    Station* st = new ChangeStation(st_num, stream, name);
    addSt(st, time, add_time);
}

skip_list<uint, Station*>::Iterator Line::find(std::string st_name){
    return line.find(stations[st_name]);
}


Station Line::findLeftNeighbor(uint st_num){
    auto it = line.find(st_num);
    return *(*it)->travelBack();
}

Station Line::findRightNeighbor(uint st_num){
    auto it = line.find(st_num);
    return *(*it)->travelForward();
}

 void Line::addChange(std::string name, Change ch){
     uint st_num = stations[name];
     auto it = line.find(st_num);
     (*it)->addChange(ch);
 }


uint Line::minTime(uint st_num1, uint st_num2){       //ищет минимальное время пути между двумя станциия
    
    if (st_num2 < st_num1){                         //упорядочивание станций(чтобы st_num2 >= st_num1)
        uint t = st_num2;
        st_num2 = st_num1;
        st_num1 = t;
    }

    auto st1 = line.find(st_num1);
    auto st2 = line.find(st_num2);


    auto current = st1;                         
    uint time = 0;              
    while (current != st2){           //подсчет времени            
        time += (*current)->travelForwardTime();
        ++current;
    }

    if(is_circle){
        uint time_rev = 0;
        while(st2 != st1){
            time_rev += (*st2)->travelForwardTime();
            ++st2;
        }
        return std::min(time, time_rev);
    }

    return time; 
}

void Line::makeCircle(uint time){
    auto end = line.end().getNode();
    auto begin = line.begin().getNode();
    end->next = begin;
    begin->previous = end;
    changeTravel(end->data, begin->data, time);
    is_circle = true;
}

uint Line::onLine(std::string name) const {
    if(stations.count(name) == 0){
        return 0;
    } else{
        return stations.at(name);
    }
}

Line& Line::operator=(const Line& l){
    if(&l != this){
        stations = l.stations;
        line = l.line;
        is_circle = l.is_circle;
    }
    return *this;
}


skip_list<uint, Station*>::Iterator operator+(skip_list<uint, Station*>::Iterator it, int n){
    it += n;
    return it;
}

skip_list<uint, Station*>::Iterator operator-(skip_list<uint, Station*>::Iterator it, int n){
    it -= n;
    return it;
}

Line::~Line(){
}