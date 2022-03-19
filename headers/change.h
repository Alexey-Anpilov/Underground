#ifndef CHANGE_H_
#define CHANGE_H_

class Node;

class Change{
private:
    Node* first_st = nullptr;   //указатель на одной узел, содержащий информацию о станции на ветке
    Node* second_st = nullptr;  //указатель на другой узел, содержащий информацию о станции на ветке
    uint time;                  //время(мин) на пересадку
    uint stream;                //средний пассажиропоток на пересадке
public: 
    Change(uint time, uint stream)
        :time(time),
         stream(stream) {}


    //получение значений полей
    
    const Node& GetFirstNode(){
        return *first_st;
    }

    const Node& GetSecondNode(){
        return *second_st;
    }

    uint GetTime() const{
        return time;
    }

    uint GetStream() const{
        return stream;
    }
};

#endif