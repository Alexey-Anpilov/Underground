#include "station.h"

void Station::ChangePassStream(uint new_stream){
    stream = new_stream;
     
}

bool Station::operator< (Station st){
        return st_num < st.GetNum();
}

bool Station::operator==(Station st){
        return st_num == st.GetNum();

}