#include"station.h"

Station::Station(const Station& st){
    this->station_num = st.station_num;
    this->stream = st.stream;
    this->name = st.name;
    this->forward = st.forward;
    this->back = st.back;
}


bool operator<(const Station& lhs, const Station& rhs){
    return lhs.getNum() < rhs.getNum();
}

bool operator==(const Station& lhs, const Station& rhs){
        return lhs.getNum() == rhs.getNum();

} 
void Station::changePassStream(int new_stream){   // изменение пассажиропотока
        stream = new_stream;
}

void Station::setTravelFor(uint time, Station* st){
    forward = Travel(this, st, time);
}

void Station::setTravelBack(uint time, Station* st){
    back = Travel(this, st, time);
}


uint Station::travelForwardTime() const{
    return forward.timeToTravel();       
}

uint Station::travelBackTime() const{
    return back.timeToTravel();
}

Station& Station::operator=(const Station& st){
    if(&st != this){
        this->station_num = st.station_num;
        this->stream = st.stream;
        this->name = st.name;
        this->forward = st.forward;
        this->back = st.back;
    }
    return *this;
}
