#ifndef LINE_H_
#define LINE_H_
#include<iostream>
#include<array>
#include"node.h"


class Line {
private:
    static uint st_count;
    const uint max_level = 3;     //максимум 3 уровня связей
    const float p = 0.5;          //вероятность при наличии i-того уровня получить (i+1) уровень  
    
    Node* header = nullptr;     //указатель на начальный элемент
    

    uint LevelRand() const;     //вычисление количества уровней для нового элемента

    Node* FindNode(uint num) const;   //поиск узла в skip-list по номеру станции

    void FindLinks(std::vector<Node*>&, const Node* node) const;    //поиск элементов, которые имеют ссылку на данный
    
    void ChangeTravel(Node* first_node, Node* second_node, uint time);    //изменение перегонов для двух станций

    void RenumStations(uint st_num);       //перенумеровка станций при добавлении в конец или середину

    void AddNode(Node* new_node);             //используется, чтобы добавить узел(в основном для функции AddStation)

    void SetFirstStation(Node* new_node);
public:
    Line(const Station& first_st);

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