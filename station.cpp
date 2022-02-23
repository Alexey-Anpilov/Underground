#include "station.h"

void Station::ChangePassStream(int new_stream){
        stream = new_stream;
}

bool Station::operator< (const Station& st){
        return station_num < st.GetNum();
}

bool Station::operator==(const Station& st){
        return station_num == st.GetNum();

}