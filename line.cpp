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



void Line::ChangeTravel(Node* first_node, Node* second_node, Node* new_node, Station* new_st){
    
    first_node->forward.SetSecond(new_st);
    first_node->forward.SetTime(new_node->back.GetTime());
    new_node->back.SetFirst(&(first_node->st));
    if (second_node != nullptr){
        new_node->forward.SetSecond(&(second_node->st));
        second_node->back.SetSecond(&new_node->st);
        second_node->back.SetTime(new_node->forward.GetTime());
    }
}



void Line::AddStation(Station* new_st, uint time_back, uint time_for){
    Node* current = header;
    std::vector<Node*> changes(max_level);
    
    if (current == nullptr){
        Node* new_node = new Node(max_level, *new_st, time_back, time_for);
        header = new_node;
        return;
    }

    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (*new_st < current->following[i]->st){
                break;
            }
            current = current->following[i];
        }
        changes[i] = current;
    }
    
    current = current->following[0];
    uint new_level = LevelRand();

    Node* new_node = new Node(new_level, *new_st, time_back, time_for);
    std::cout << new_node->st.GetName();

    ChangeTravel(changes[0], current, new_node, new_st);


    for(uint i = 0; i <= new_level; i++){
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
    
}

Line::Node* Line::FindNode(uint num){
    Node* current = header;

    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (num < current->following[i]->st.GetNum()){
                break;
            }
            current = current->following[i];
        }
    }

    return current;
}

std::pair<Station, uint> Line::FindLeftNeighbor(uint num){
    Node* node = FindNode(num);
    return {node->back.GetFirstStation(), node->back.GetTime()};
}


std::pair<Station, uint> Line::FindRightNeighbor(uint num){
    Node* node = FindNode(num);
    return {node->forward.GetSecondStation(), node->forward.GetTime()};
}

void Line::PrintLine() const{
    Node* it = header;
    while(it != nullptr){
        std::cout << "Number: "<< it->st.GetNum() << std::endl << "Name: "
                  << it->st.GetName() << std:: endl << "Stream: " << it->st.GetStream() << std::endl;
        it = it->following[0];
    }
}