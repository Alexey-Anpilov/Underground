#include"line.h"


uint Line::LevelRand() const{
    uint level = 1;
    float r = (float)rand()/RAND_MAX;
    while(level < max_level && r < p){
        ++level;
        r = (float)rand()/RAND_MAX;
    }
    return level;
}



void Line::ChangeTravel(Node* first_node, Node* second_node, Node* new_node){
    first_node->forward.second_st = &new_node->st;
    first_node->forward.time = new_node->back.GetTime();
    new_node->back.first_st = &first_node->st;
    if (second_node != nullptr){
        second_node->back.second_st = &new_node->st;
        second_node->back.time = new_node->forward.GetTime();
        new_node->forward.second_st = &second_node->st;
    }
}

Line::Node* Line::FindNode(uint num) const{
    Node* current = header;

    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (num < current->following[i]->st.GetNum() || current->following[i] == header){
                break;
            }
            current = current->following[i];
        }
    }

    return current;
}


void Line::AddStation(const Station* new_st, uint time_back, uint time_for){
    Node* current = header;
    std::vector<Node*> changes(max_level);    
    if (current == nullptr){
        Node* new_node = new Node(max_level, *new_st);
        header = new_node;
        return;
    }

    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (*new_st < current->following[i]->st || current->following[i] == header){
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


    for(uint i = 0; i <= new_level; i++){
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
    
}

void Line::MakeCircle(uint time){
    Node* current = header;
    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            current = current->following[i];
        }
    }
    header->back.time = time;      
    current->forward.time = time;
    for(auto& it : current->following){
        it = header;
    }
    return;
}


std::pair<Station, uint> Line::FindLeftNeighbor(uint num) const{
    Node* node = FindNode(num);
    return {node->back.GetFirstStation(), node->back.GetTime()};
}


std::pair<Station, uint> Line::FindRightNeighbor(uint num) const{
    Node* node = FindNode(num);
    return {node->forward.GetSecondStation(), node->forward.GetTime()};
}

uint Line::MinTime(uint st_num1, uint st_num2) const{
    if (st_num2 < st_num1){
        uint t = st_num2;
        st_num2 = st_num1;
        st_num1 = t;
    }

    Node* node1 = FindNode(st_num1);
    Node* current = node1;
    Node* node2 = FindNode(st_num2);

    uint time = 0;
    while (current != node2){
        time += current->forward.GetTime();
        current = current->following[0];
    }
    
    if (header->back.GetTime() != 0){
        
        uint time_rev = 0;
        while(node2 != node1){
            time_rev += node2->forward.GetTime();
            node2 = node2->following[0];
        }
        return std::min(time, time_rev);

    }

    return time; 
}


void Line::PrintLine() const{
    Node* it = header;
    while(it != nullptr){
        std::cout << "Number: "<< it->st.GetNum() << std::endl << "Name: "
                  << it->st.GetName() << std:: endl << "Stream: " << it->st.GetStream() << std::endl;
        it = it->following[0];
    }
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

