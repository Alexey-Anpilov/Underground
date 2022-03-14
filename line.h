#ifndef LINE_H_
#define LINE_H_
#include<iostream>
#include<array>
#include"node.h"


class Line {
private:
    const uint max_level = 3;     //максимум 3 уровня связей
    const float p = 0.5;          //вероятность при наличии i-того уровня получить (i+1) уровень  
    
    Node* header = nullptr;     //указатель на начальный элемент
    

    uint LevelRand() const;     //вычисление количества уровней для нового элемента

    Node* FindNode(uint num) const;   //поиск узла в skip-list по номеру станции

    void ChangeTravel(Node* first_node, Node* second_node, Node* new_node);    //изменение указателей в перегонах при добавлении новой станции между двумя другими

    void RenumStations(uint st_num);       //перенумеровка станций при добавлении в конец или середину

    //void SetFirstStation(const Station*);    //функция обрабатывает случай, когда заменяется первая станция
public:
    Line(const Station* first_st);

    void AddStation(const Station* new_st, uint time_back, uint time_for = 0);  //добавление станции

    void MakeCircle(uint time);                             //можно сделать линию кольцевой

    std::pair<Station, uint> FindRightNeighbor(uint num) const;   //поиск правой соседней станции и времени перегона до нее

    std::pair<Station, uint> FindLeftNeighbor(uint num) const;    //поиск левой соседней станции и времени перегона до нее

    uint MinTime(uint st_num1, uint st_num2) const;               //оценка минимального времени для перемещения между двумя станциями

    void PrintLine() const;     //вывод всех станций линии

    const Station& GetSt(uint st_num) const;       //для тестирования

    ~Line();
};


#endif