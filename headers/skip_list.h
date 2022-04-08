#ifndef SKIP_LIST_
#define SKIP_LIST_
#include<vector>

template<typename KEY, typename DATA>
class skip_list{
private:
    static uint s;
    const uint max_level = 3;       
    const float p = 0.5;

    struct node{
        KEY key;
        DATA data;
        std::vector<node*> following;
        node* previous;
        node* next;
        node(uint lvl, const KEY& key, const DATA& data, node* previous = nullptr, node* next = nullptr)
            :key(key),
             data(data),
             following(lvl, nullptr),  
             previous(previous),
             next(next) {}
    };

    node* header = nullptr;

    uint levelRand() const;

    std::vector<node*> findLinks(const node* node_) const;

    node* findLower(const KEY& key) const;

    node* findNode(const KEY& key) const;
public:
    class Iterator{
    private:
        skip_list* current_list;
        node* current_node;
    public:
        Iterator(skip_list& skip_list);
        Iterator(skip_list& skip_list, node* current_node);
        Iterator(const Iterator& it);
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator& operator+=(uint n);
        Iterator& operator-=(uint n);
        DATA& operator*() const;
        Iterator& operator=(const Iterator& it);
        bool operator!=(const Iterator& it);
        bool operator==(const Iterator& it);
        bool empty();
        node* getNode();
    };

    Iterator begin();
    Iterator end();

    static uint size(){
        return s;
    }

    Iterator add(const KEY& key, const DATA& data);

    Iterator find(const KEY& key);

    ~skip_list();
};

template<typename KEY, typename DATA>
uint skip_list<KEY, DATA>::s = 0;

//------Private методы------
template<typename KEY, typename DATA>
uint skip_list<KEY, DATA>::levelRand() const{                   //вычисление количества уровней связей для добавляемого элемента;
    uint level = 1;                                       //вероятность получить еще один уровень каждый раз равна p
    float r = (float)rand()/RAND_MAX;
    while(level < max_level && r < p){
        ++level;
        r = (float)rand()/RAND_MAX;
    }
    return level;
}


template<typename KEY, typename DATA>
std::vector<typename skip_list<KEY, DATA>::node*> skip_list<KEY, DATA>::findLinks(const node* node_) const{
    std::vector<node*> links(max_level);
    node* current = header;
    for(int i = max_level - 1; i >= 0; --i){                                                        
        while(current->following[i] != nullptr){                                                    
            if (node_ != nullptr){
                if (node_->key <= current->following[i]->key){  //попадает либо на больший, либо на начальный(для кольцевой), либо совпадает с входным 
                    break;
                }
            }
            current = current->following[i];
        }
        links[i] = current;
    }
    return links;
}


template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::node* skip_list<KEY, DATA>::findLower(const KEY& key) const{
    node* current = header;
    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (key < current->following[i]->key){      
                break;
            }
            current = current->following[i];
        }
    }
    return current;
}

template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::node* skip_list<KEY, DATA>::findNode(const KEY& key) const{
    node* current = header;
    for(int i = max_level - 1; i >= 0; --i){
        while(current->following[i] != nullptr){
            if (key < current->following[i]->key){      
                break;
            }
            current = current->following[i];
        }
    }
    if (key != current->key){
        return nullptr;
    }else{
        return current;
    }
}



//------Public методы------

template<typename KEY, typename DATA>
skip_list<KEY, DATA>::Iterator::Iterator(skip_list& skip_list)
    :current_list(&skip_list),
     current_node(skip_list.header) {}


template<typename KEY, typename DATA>
skip_list<KEY, DATA>::Iterator::Iterator(const Iterator& it)
    :current_list(it.current_list),
     current_node(it.current_node) {}

template<typename KEY, typename DATA>
skip_list<KEY, DATA>::Iterator::Iterator(skip_list& skip_list, node* current_node)
    :current_list(&skip_list),
     current_node(current_node) {}

template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator& skip_list<KEY, DATA>::Iterator::operator++(){
    if (current_node != nullptr){
        current_node = current_node->next;
    }
    return *this;
}

template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator skip_list<KEY, DATA>::Iterator::operator++(int){
    Iterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator& skip_list<KEY, DATA>::Iterator::operator--(){
    if(current_node != nullptr){
        current_node = current_node->previous;
    }
    return *this;
}


template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator skip_list<KEY, DATA>::Iterator::operator--(int){
    Iterator tmp(*this);
    --(*this);
    return tmp;
}


template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator& skip_list<KEY, DATA>::Iterator::operator+=(uint n){
    for(uint i = 0; i < n && current_node != nullptr; ++i){
        current_node = current_node->next;
    }
    return *this;
}



template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator& skip_list<KEY, DATA>::Iterator::operator-=(uint n){
    for(uint i = n; i > 0 && current_node != nullptr; --i){
        current_node = current_node->previous;
    }
    return *this;
}


template<typename KEY, typename DATA>
DATA& skip_list<KEY, DATA>::Iterator::operator*() const{
    return current_node->data;
}


template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator& skip_list<KEY, DATA>::Iterator::operator=(const skip_list::Iterator& it){
    current_list = it.current_list;
    current_node = it.current_node;
    return *this;
} 

template<typename KEY, typename DATA>
bool skip_list<KEY, DATA>::Iterator::operator!=(const skip_list::Iterator& it){
    return (this->current_list != it.current_list) || (this->current_node != it.current_node);
}

template<typename KEY, typename DATA>
bool skip_list<KEY, DATA>::Iterator::operator==(const skip_list::Iterator& it){
    return (this->current_list == it.current_list) && (this->current_node == it.current_node);
}

template<typename KEY, typename DATA>
bool skip_list<KEY, DATA>::Iterator::empty(){
    if (this->current_node == nullptr){
        return true;
    }else return false;
}

template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::node* skip_list<KEY, DATA>::Iterator::getNode(){
    return current_node;
}

template<typename KEY,typename DATA>
typename skip_list<KEY, DATA>::Iterator skip_list<KEY, DATA>::begin(){
    return Iterator(*this);
}


template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator skip_list<KEY, DATA>::end(){
    Iterator it = Iterator(*this);
    it += this->size() - 1;
    return it;
}



template<typename KEY, typename DATA>
typename skip_list<KEY, DATA>::Iterator skip_list<KEY, DATA>::add(const KEY& key, const DATA& data){ 
    s++;
    if (header == nullptr){
        node *new_node = new node(max_level, key, data);
        header = new_node;
        return Iterator(*this);
    }
    if (key < header->key){
        node *new_node = new node(max_level, key, data);
        new_node->next = header;
        header->previous = new_node;
        for(uint i = 0; i < max_level; i++){
            new_node->following[i] = header;
        }
        header = new_node;
        return Iterator(*this);
    }
    node* current = findLower(key);   //ищем узел после которого надо добавить
    node* new_node = new node(levelRand(), key, data);
    new_node->previous = current;
    current->next = new_node;
    current = current->following[0];
    new_node->next = current;
    if (current != nullptr){
        current->previous = new_node;
    }
    std::vector<node*> changes(max_level);
    changes = findLinks(current);    //массив со связями для нового узла
    

    for(uint i = 0; i < new_node->following.size(); i++){   //в цикле создаются корректные связи между узлами в skip-list
        new_node->following[i] = changes[i]->following[i];
        changes[i]->following[i] = new_node;
    }
    
    return Iterator(*this, new_node);
}

template<typename KEY, typename DATA>
typename skip_list<KEY,DATA>::Iterator skip_list<KEY, DATA>::find(const KEY& key){
    node* p = findNode(key);
    return Iterator(*this, p);
}


template<typename KEY, typename DATA>
skip_list<KEY, DATA>::~skip_list(){
    node* current = header;
    node* previous;
    while(current->following[0] != nullptr){
        previous = current;
        current = current->following[0];
        delete previous;
    }
    delete current;
}
#endif
