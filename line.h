#ifndef LINE_H_
#define LINE_H_

#include<vector>
#include"travel.h"

class Line{
private:
    std::vector<Travel> line; // линия представляет собой вектор из перегонов(travel)
public:
    Line(const std::vector<Travel> line)
        :line(line){}

    void AddStation(Station& new_station, uint time);

    std::vector<Travel>::const_iterator FindStation(const std::string& name) const;
    
    std::pair<Station&, uint> FindRightNeighbor(const std::string& name) const;

    std::pair<Station&, uint> FindLeftNeighbor(const std::string& name) const;

    uint FindMinTime(std::string st1, std::string name) const;
};

#endif