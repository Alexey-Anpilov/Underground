#ifndef TRAVEL_H_
#define TRAVEL_H_

class Station;

class Travel{
private:
    uint time;                      //время прогона(мин)
    Station* first_st;              //указатель на первую станцию
    Station* second_st;             //указатель на вторую станцию
    friend class Station;
public:
    Travel(){
        time = 0;
        first_st = nullptr;
        second_st = nullptr;
    }

    Travel(Station* first_st, Station* second_st, uint time)
        :time(time),
         first_st(first_st),
         second_st(second_st) {}


    const Station& travel() const{
        return *second_st;
    }


    const Station& stay() const{
        return *first_st;
    }

    uint timeToTravel() const{
        return time;
    }
};

#endif