#ifndef LINE_H_
#define LINE_H_

#include<vector>
#include"station.h"
#include "travel.h"
#include<iostream>
#include<array>

class Line {
private:
    const uint max_level = 3;     //максимум 3 уровня связей
    const float p = 0.5;          //вероятность при наличии i-того уровня получить (i+1) уровень  
    
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
    
    Node* header = nullptr;     //указатель на начальный элемент
    

    uint LevelRand() const;     //вычисление количества уровней для нового элемента

    Node* FindNode(uint num) const;   //поиск узла в skip-list по номеру станции

    void ChangeTravel(Node* first_node, Node* second_node, Node* new_node);    //изменение указателей в перегонах при добавлении новой станции между двумя другими

public:
    Line(const Station* first_st);

    void AddStation(const Station* new_st, uint time_back, uint time_for = 0);  //добавление станции

    void MakeCircle(uint time);                             //можно сделать линию кольцевой

    std::pair<Station, uint> FindRightNeighbor(uint num) const;   //поиск правой соседней станции и времени перегона до нее

    std::pair<Station, uint> FindLeftNeighbor(uint num) const;    //поиск левой соседней станции и времени перегона до нее

    uint MinTime(uint st_num1, uint st_num2) const;               //оценка минимального времени для перемещения между двумя станциями

    void PrintLine() const;     //вывод всех станций линии

    Station GetSt(uint st_num) const;       //для тестирования

    ~Line();
};


#endif