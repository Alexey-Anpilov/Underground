#include "station.h"

void Station::ChangePassStream(uint new_stream){
    stream = new_stream;
     
}

bool Station::operator< (const Station& st){
        return st_num < st.GetNum();
}

bool Station::operator==(const Station& st){
        return st_num == st.GetNum();

}