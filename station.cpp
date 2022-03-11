#include"station.h"

bool operator<(const Station& lhs, const Station& rhs){
    return lhs.GetNum() < rhs.GetNum();
}

bool operator==(const Station& lhs, const Station& rhs){
        return lhs.GetNum() == rhs.GetNum();

} 
void Station::ChangePassStream(int new_stream){   // изменение пассажиропотока
        stream = new_stream;
    }