#include"line.h"
#include<iostream>

void Line::AddStation(Station& new_st){
    Node* new_node = new Node(new_st);
    Node* ptr = root;
    Node* pprev_node;
    Node* prev_node;
    while(ptr != nullptr){
        prev_node = ptr;
        if (new_st < ptr->st){
            ptr = ptr->left;
        } else{
            ptr= ptr->right;
        }
    }
    if (prev_node == nullptr){
       root = new_node; 
    } else{
        if (new_st < prev_node->st){
            Node* t = prev_node->left;
            prev_node->l = 0;
            prev_node->left = new_node;
            new_node->left = t;
            new_node->l = 1;
            new_node->r = 1;
            new_node->right = prev_node;
        }
        else{
            Node* t = prev_node->right;
            prev_node->r = 0;
            prev_node->right = new_node;
            new_node->right = t;
            new_node->l = 1;
            new_node->r = 1;
            new_node->left = prev_node; 
        }
    }
}

void Line::PrintLine() const{
    Node* p = root;
    while(p != nullptr){
        std::cout << p->st.GetNum() << " " << p->st.GetName() << std::endl;
        p = p->right;
    }
}




/*Node* new_node = new Node(new_st);
    Node* ptr = root;
    Node* pprev_node;
    Node* prev_node;
    int r = 0, l = 0;
    pprev_node = ptr;
    prev_node = ptr;
    while(ptr != nullptr){
        if (new_st < ptr->st){
            if (r == 1){
                pprev_node = prev_node;
                r = 0;
            }
            l = 1;
            prev_node = ptr;
            ptr = ptr->left;
        } else{
            if(l == 1){
                pprev_node = prev_node;
                l = 0;
            }
            r = 1;
            prev_node = ptr;
            ptr = ptr->right;
        }
    }
    if (prev_node == nullptr){
       root = new_node; 
    } else{
        if (r == 1){
            prev_node->right = new_node;
            prev_node->r = 0;
            
        }
    }*/