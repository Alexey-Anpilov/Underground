#ifndef LINE_H_
#define LINE_H_

#include<vector>
#include"station.h"
#include "travel.h"
#include<iostream>

class Line {
private:
    uint max_level = 3;     //максимум 3 уровня связей
    float p = 0.5;          //вероятность при наличии i-того уровня получить (i+1) уровень  
    class Node{
    public:
        std::vector<Node*> following;
        Station st;
        Travel forward;
        Travel back;
        Node(uint lvl, Station new_st, uint time_back, uint time_for)
            :following(lvl, nullptr),
             st(new_st),
             forward(time_for),
             back(time_back) {
                 forward.SetFirst(&st);
                 back.SetSecond(&st);
             }
    };
    
    Node* header = nullptr;

    uint LevelRand() const;  //вычисление количества уровней для нового элемента

    Node* FindNode(uint num);

    void ChangeTravel(Node* first_node, Node* second_node, Node* new_node, Station* new_st);

public:
    void AddStation(Station* new_st, uint time_back, uint time_for = 0);

    std::pair<Station, uint> FindRightNeighbor(uint num);

    std::pair<Station, uint> FindLeftNeighbor(uint num);

    void PrintLine() const;

};


#endif