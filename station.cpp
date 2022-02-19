#include "station.h"

bool Station::ChangePassStream(int new_stream){
    if(new_stream >= 0){
        stream = new_stream;
        return true;
    } else {
        return false;
    }
}

bool Station::operator< (const Station& st){
        return station_num < st.GetNum();
}

bool Station::operator==(const Station& st){
        return station_num == st.GetNum();

}