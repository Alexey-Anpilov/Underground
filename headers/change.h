#ifndef CHANGE_H_
#define CHANGE_H_

class Station;

class Change{
private:
    uint time;                  //время(мин) на пересадку
    uint stream;                //средний пассажиропоток на пересадке
    Station* first_st;   //указатель на одной узел, содержащий информацию о станции на ветке
    Station* second_st;  //указатель на другой узел, содержащий информацию о станции на ветке
public: 
    Change(uint time, uint stream, Station* first_st = nullptr, Station* second_st = nullptr)
        :time(time),
         stream(stream),
         first_st(first_st),
         second_st(second_st) {}


    //получение значений полей
    uint getTime() const{
        return time;
    }

    uint getStream() const{
        return stream;
    }
};

#endif