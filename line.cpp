#include"line.h"

//-----------Private методы-------------


uint Line::LevelRand() const{                   //вычисление количества уровней связей для добавляемого элемента;
    uint level = 1;                             //вероятность получить еще один уровень каждый раз равна p
    float r = (float)rand()/RAND_MAX;
    while(level < max_level && r < p){
        ++level;
        r = (float)rand()/RAND_MAX;
    }
    return level;
}


Node* Line::FindNode(uint num) const{                //поиск узла в skip-list по номеру станции
    Node* current = header;
    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (num < current->following[i]->st->GetNum() || current->following[i] == header){
                break;
            }
            current = current->following[i];
        }
    }

    return current;
}


void Line::ChangeTravel(Node* first_node, Node* second_node, Node* new_node){       //при добавлении новой станции между двумя другими необходимо перепривязать перегоны
    first_node->forward.second_st = new_node->st;
    first_node->forward.time = new_node->back.GetTime();
    new_node->back.first_st = first_node->st;
    if (second_node != nullptr){
        second_node->back.first_st = new_node->st;
        second_node->back.time = new_node->forward.GetTime();
        new_node->forward.second_st = second_node->st;
    }
}


void Line::RenumStations(uint st_num){          //перенумеровка станций при добавлении в середину/начало ветки
    Node* current = header;
    while (current->st->GetNum() != st_num){     //находим откуда надо менять
        current = current->following[0];
    }
    while(current->following[0] != nullptr && current->following[0] != header){         //меняем в цикле номера для всех последующих станций
        st_num++;
        current->st->SetStNum(st_num);
        current = current->following[0];
    }
    current->st->SetStNum(st_num + 1);
}


void Line::AddNode(Node* new_node){           //добавляет узел в skip-list 
    Node* current = header;
    std::vector<Node*> changes(max_level);    //массив со связями для нового узла
    for(int i = max_level - 1; i >= 0; --i){                                                        //в цикле находится место куда вставить новый узел;
        while(current->following[i] != nullptr){                                                    //в changes вносится узел после которого надо вставить новый
            if (*new_node->st < *current->following[i]->st || current->following[i] == header){
                break;
            }
            current = current->following[i];
        }
        changes[i] = current;
    }

    current = current->following[0]; //если вставляется между двумя узлами, то этот будет правый
    
    ChangeTravel(changes[0], current, new_node);        //для трех узлов происходит корректное переназначение прогонов
    
    for(uint i = 0; i < new_node->following.size(); i++){   //в цикле создаются корректные связи между узлами в skip-list
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
}

void Line::SetFirstStation(Node* new_node){         //добавляет узел в начало
    for(uint i = 0; i < max_level; i++){
        new_node->following[i] = header;
    }
    if (header->back.GetTime() == 0){               
        header->back.time = new_node->forward.time;     
        header->back.first_st = new_node->st;
        new_node->forward.second_st = header->st;
    }/*else {
       Node* current = header;
       for(int i = max_level - 1; i >= 0; --i){                                                        
            while(current->following[i] != header){                                                    
                current = current->following[i];
            }
        current->following[i] = new_node;
        }
        ChangeTravel(current, header, new_node);
    }*/
    header = new_node;
}

//--------Public методы----------


Line::Line(const Station& first_st){
    st_count++;
    header = new Node(max_level, first_st);
}

/*
* Метод Line::AddStation позволяет добавить новую станцию в skip-list.
* time_back - время прогона от старой станции до новой
* time_for - время прогона от новой станции до следующей после нее(используется при добавлении станции между двумя другими)
* Метод обрабатывает делает предварительную обработку: перенумеровывает станции, создает новый узел с нужным количеством связей. 
* Узел добавляется в структуру private методом AddNode или SetFirstStation
*/

void Line::AddStation(const Station* new_st, uint time_back, uint time_for){ 
    Node* new_node;
    if(new_st->GetNum() == 1){            //если меняется первая станция 
        RenumStations(1);
        new_node = new Node(max_level, *new_st, time_back, time_for);
        SetFirstStation(new_node);        
        return;
    }
    if(new_st->GetNum() <= st_count){ 
            RenumStations(new_st->GetNum());    //если добавляется в произвольное место
    }
    st_count++;
    uint new_level = LevelRand();  
    new_node = new Node(new_level, *new_st, time_back, time_for);
    AddNode(new_node);
}


void Line::MakeCircle(uint time){       //используется, чтобы сделать линию кольцевой
    Node* current = header;
    for(int i = max_level - 1; i >= 0; --i){            //находим последний узел
        while(current->following[i] != nullptr){
            current = current->following[i];
        }
    }
    
    header->back.time = time;                           //переделываем связи
    header->back.first_st = current->st;
    current->forward.time = time;
    current->forward.second_st = header->st;
    for(auto& it : current->following){
        it = header;
    }
}


std::pair<Station, uint> Line::FindRightNeighbor(uint num) const{       //возвращает правую соседнюю станцию и время прогона до нее
    Node* node = FindNode(num);
    return {node->forward.GetSecondStation(), node->forward.GetTime()};
}


std::pair<Station, uint> Line::FindLeftNeighbor(uint num) const{        //возвращает левую соседнюю станцию и время прогона до нее
    Node* node = FindNode(num);
    return {node->back.GetFirstStation(), node->back.GetTime()};
}


uint Line::MinTime(uint st_num1, uint st_num2) const{       //ищет минимальное время пути между двумя станциия
    
    if (st_num2 < st_num1){                         //упорядочивание станций(чтобы st_num2 >= st_num1)
        uint t = st_num2;
        st_num2 = st_num1;
        st_num1 = t;
    }

    Node* node1 = FindNode(st_num1);                //поиск первой и второй станций в skip-list
    Node* node2 = FindNode(st_num2);


    Node* current = node1;                          //подсчет времени
    uint time = 0;
    while (current != node2){               
        time += current->forward.GetTime();
        current = current->following[0];
    }
    

    if (header->back.GetTime() != 0){               //если кольцевая то нужно сравнивать время для двух разных путей
        uint time_rev = 0;
        while(node2 != node1){
            time_rev += node2->forward.GetTime();
            node2 = node2->following[0];
        }
        return std::min(time, time_rev);

    }

    return time; 
}


void Line::PrintLine() const{                      //Печать информации о станциях на линии
    Node* it = header;
    while(it != nullptr){
        std::cout << "Number: "<< it->st->GetNum() << std::endl << "Name: "
                  << it->st->GetName() << std:: endl << "Stream: " << it->st->GetStream() << std::endl;
        it = it->following[0];
        if (it == header){
            break;
        }
    }}

const Station& Line::GetSt(uint st_num) const{
    return *FindNode(st_num)->st;
}   

Line::~Line(){
    Node* current = header;
    Node* previous;
    while(current->following[0] != nullptr){
        if(current->following[0] == header){
            break;
        }
        previous = current;
        current = current->following[0];
        delete previous;
    }
    delete current;
}






/*
void Line::AddStation(const Station* new_st, uint time_back, uint time_for){ 
    Node* current = header;
    std::vector<Node*> changes(max_level);    //массив со связями для нового узла
    bool not_end = false;
    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (*new_st < *current->following[i]->st || current->following[i] == header){
                break;
            }
            if (*new_st == *current->following[i]->st){
                not_end = true;
                break;
            }
            current = current->following[i];
        }
        changes[i] = current;
    }
    
    current = current->following[0]; //если вставляется между двумя узлами, то этот будет правый
    uint new_level = LevelRand();

    Node* new_node = new Node(new_level, *new_st, time_back, time_for);

    ChangeTravel(changes[0], current, new_node);


    for(uint i = 0; i < new_level; i++){
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
    
    if(not_end){
        RenumStations(new_node->st->GetNum());
    }
}*/