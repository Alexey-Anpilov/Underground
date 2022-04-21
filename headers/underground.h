#ifndef UNDERGROUND_H_
#define UNDERGROUND_H_
#include"line.h"
#include<list>
#include<set>

class Underground{
private:
    std::vector<Line> lines;

    skip_list<uint, Station*>::Iterator findStation(std::string name) const;
public:
    void addLine(Line new_line);

    std::pair<uint, std::vector<std::string>> timeMinPath(std::string first_st_name, std::string second_st_name);

    std::list<std::string> streamMinPath() const;
};

#endif
