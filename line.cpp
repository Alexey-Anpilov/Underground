#include"line.h"

void Line::AddStation(Station& new_station, uint time){
    Travel new_travel = Travel(line.back().GetSecondStation(), new_station, time);
    line.push_back(new_travel);
}

std::vector<Travel>::const_iterator Line::FindStation(const std::string& name) const{
    for(auto it = begin(line); it != end(line); ++it){
        if((*it).GetFirstStation().GetName() == name || (*it).GetSecondStation().GetName() == name){
            return it;
        }
    }
}

std::pair<Station&, uint> Line::FindRightNeighbor(const std::string& name) const{
    for(const Travel& tr : line){
        if(tr.GetFirstStation().GetName() == name){
            return {tr.GetSecondStation(), tr.GetTime()};
        }
    }    
}

std::pair<Station&, uint> Line::FindLeftNeighbor(const std::string& name) const{
    for(const Travel& tr : line){
        if(tr.GetSecondStation().GetName() == name){
            return {tr.GetFirstStation(), tr.GetTime()};
        } 
    }
}    


uint Line::FindMinTime(std::string st1, std::string st2) const{
    if (st1 == st2){
        return 0;
    }
    auto it1 = this->FindStation(st1);
    auto it2 = this->FindStation(st2);
    uint result = 0;
    if (it1 > it2){
        auto t = it2;
        it2 = it1;
        it1 = t;
        auto t2 = st2;
        st2 = st1;
        st1 = t2;
    }
    
    if ((*it1).GetFirstStation().GetName() == st1){
        result += (*it1).GetTime();
    }

    if ((*it2).GetSecondStation().GetName() == st2){
        result += (*it2).GetTime();
    }
    it1++;
    for(auto it = it1; it1 != it2; it1++){
        result += (*it).GetTime();
    }
    return result;
}