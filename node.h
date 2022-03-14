#ifndef NODE_H_
#define NODE_H_
#include<vector>
#include"station.h"
#include "travel.h"


//элементы в skip-list
    class Node{
    public:
        std::vector<Node*> following;  //указатели на следующие элементы по уровням начиная с 1 до 3
        Station st;                    //станция
        Travel forward;                //перегон(мин) до следующей станции
        Travel back;                   //перегон(мин) до предыдущей станции
        
        Node(uint lvl,const Station& new_st, uint time_back = 0, uint time_for = 0)
            :following(lvl, nullptr),
             st(new_st),
             forward(time_for),
             back(time_back) {
                 forward.first_st = &st;
                 back.second_st = &st;
             }
    };

#endif