#ifndef REGULAR_STATION_H_
#define REGULAR_STATION_H_

#include <string>
class RegularStation{
private:
    int pass_stream;
    int station_num;
    std::string name;

    void ChangePassStream(const int& new_pass_stream);

public:
    RegularStation(int pass_stream, int st_num, std::string name) 
        :pass_stream(pass_stream),
         station_num(st_num),
         name(name) {}   

    
    bool operator<(const RegularStation& st); 
    
    bool operator==(const RegularStation& st);

    int GetNum() const;
    
};

#endif