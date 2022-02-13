#include "RegularStation.h"

void RegularStation::ChangePassStream(const int& new_pass_stream){
    pass_stream = new_pass_stream;
}

bool RegularStation::operator< (const RegularStation& st){
        return station_num < st.GetNum();
}

bool RegularStation::operator==(const RegularStation& st){
        return station_num == st.GetNum();

}

int RegularStation::GetNum() const{
    return station_num;
}