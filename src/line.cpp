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


void Line::addStation(uint st_num, uint stream, std::string name, uint time, uint add_time){
    Station* st = new Station(st_num, stream, name);
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

const Station& Line::find(uint st_num){
    auto it = line.find(st_num);
    return *(*it);
}     

Station Line::findLeftNeighbor(uint st_num){
    auto it = line.find(st_num);
    return (*it)->travelBack();
}

Station Line::findRightNeighbor(uint st_num){
    auto it = line.find(st_num);
    return (*it)->travelForward();
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

skip_list<uint, Station*>::Iterator operator+(skip_list<uint, Station*>::Iterator it, int n){
    it += n;
    return it;
}

skip_list<uint, Station*>::Iterator operator-(skip_list<uint, Station*>::Iterator it, int n){
    it -= n;
    return it;
}

