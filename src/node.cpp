#include"node.h"

Node::Node (uint lvl,const Station& new_st, uint time_back, uint time_for)
            :following(lvl, nullptr),
             forward(time_for),
             back(time_back){
                st = new Station(new_st);
                forward.first_st = st;
                back.second_st = st;
             }

Node::~Node(){
    delete st;
}