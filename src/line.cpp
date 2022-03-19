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
            if (num < current->following[i]->st->GetNum() || current->following[i] == header){      //следующая связь попадает либо на элемент больше входного, либо на header для кольцевой
                break;
            }
            current = current->following[i];
        }
    }
    return current;
}

void Line::FindLinks(std::vector<Node*>& links,const Node* node) const{     //поиск узлов, которые указывают на входной
    Node* current = header;
    if (node == header){                                    //обработка случая для кольцевой линии и входного узла header
        for(int i = max_level - 1; i >= 0; --i){
            while(current->following[i] != header){
                current = current->following[i];
            }
            links[i] = current;
        }
    } else{
        for(int i = max_level - 1; i >= 0; --i){                                                        
            while(current->following[i] != nullptr){                                                    
                if (node != nullptr){
                    if (*node->st < *current->following[i]->st || current->following[i] == header || *node->st == *current->following[i]->st){  //попадает либо на больший, либо на начальный(для кольцевой), либо совпадает с входным 
                        break;
                    }
                }
                current = current->following[i];
            }
            links[i] = current;
        }
    }
}

void Line::ChangeTravel(Node* first_node, Node* second_node, uint time){       //при добавлении новой станции необходимо изменить перегоны
    first_node->forward.time = time;
    second_node->back.time = time;
    second_node->back.first_st = first_node->st;
    first_node->forward.second_st = second_node->st;
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
    Node* current = FindNode(new_node->st->GetNum());   //ищем узел после которого надо добавить
    std::vector<Node*> changes(max_level);    //массив со связями для нового узла
    current = current->following[0];
    FindLinks(changes, current);    //находим ссылки для будущего нового узла
    
    ChangeTravel(changes[0], new_node, new_node->back.time);        //меняем перегоны для нового узла и предшествующего ему
    if (current != nullptr){
        ChangeTravel(new_node, current, new_node->forward.time);    //меняем перегоны для нового узла и узла после него(если таковой есть)
    }

    for(uint i = 0; i < new_node->following.size(); i++){   //в цикле создаются корректные связи между узлами в skip-list
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
}

void Line::SetFirstStation(Node* new_node){         //добавляет узел в начало
    for(uint i = 0; i < max_level; i++){            //устанавливаем все связи на header(они оба имеют максимум уровней, как начальные)
        new_node->following[i] = header;
    }
    if (header->back.time != 0){                    //случай для кольцевой линии(необходимо обработать связи, попадающие на header)
        std::vector<Node*> links(max_level);
        FindLinks(links, header);
        for(uint i = 0; i < new_node->following.size(); i++){   //теперь все связи указывают на новый узел 
            links[i]->following[i] = new_node;
        }
        ChangeTravel(links[0], new_node, new_node->back.time);  //меняем перегоны для нового узла и предшествующего ему
    }
    ChangeTravel(new_node, header, new_node->forward.time);     //меняем перегоны для нового узла и узла после него
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
        st_count++;
        RenumStations(1);
        new_node = new Node(max_level, *new_st, time_back, time_for);
        SetFirstStation(new_node);        
        return;
    }else {
        if(new_st->GetNum() <= st_count){ 
            RenumStations(new_st->GetNum());    //если добавляется в произвольное место
        }
        st_count++;
        uint new_level = LevelRand();  
        new_node = new Node(new_level, *new_st, time_back, time_for);
        AddNode(new_node);
    }
}


void Line::MakeCircle(uint time){       //используется, чтобы сделать линию кольцевой
    
    Node* current = FindNode(st_count);                  //находим последний узел
    ChangeTravel(current, header, time);                 //переделываем прогоны

    std::vector<Node*> links(max_level);
    FindLinks(links, nullptr);                           //находим связи, которые попадают в nullptr
    for(int i = max_level - 1; i >=0; --i){              //переназначаем связи на header
        links[i]->following[i] = header;
    }
}


std::pair<Station, uint> Line::FindRightNeighbor(uint num) const{       //возвращает правую соседнюю станцию и время прогона до нее
    Node* node = FindNode(num);
    return {node->forward.GetSecondStation(), node->forward.time};
}


std::pair<Station, uint> Line::FindLeftNeighbor(uint num) const{        //возвращает левую соседнюю станцию и время прогона до нее
    Node* node = FindNode(num);
    return {node->back.GetFirstStation(), node->back.time};
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
        time += current->forward.time;
        current = current->following[0];
    }
    

    if (header->back.time != 0){               //если кольцевая то нужно сравнивать время для двух разных путей
        uint time_rev = 0;
        while(node2 != node1){
            time_rev += node2->forward.time;
            node2 = node2->following[0];
        }
        return std::min(time, time_rev);

    }

    return time; 
}


void Line::PrintLine() const{                      //вывод структуры skip-list(очень минималистичный);в очередной строке выводятся все станции на уровне начиная с максимального
    for(int i = max_level - 1; i >= 0; --i){
        Node* current = header;
        while(current->following[i] != nullptr && current->following[i] != header){
            std::cout << current->st->GetName() << "  ";
            current = current->following[i];
        }
        std::cout << current->st->GetName() << std::endl;
    }
}

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