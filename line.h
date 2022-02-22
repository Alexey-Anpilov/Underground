#ifndef LINE_H_
#define LINE_H_

#include<vector>
#include"travel.h"

struct Node{
    Station st;
    Node* left = nullptr;
    Node* right = nullptr;
    uint8_t l = 0;
    uint8_t r = 0;

    Node(Station st)
        :st(st) {}
};

class Line{
private:
    Node* root = nullptr;
public:
    void AddStation(Station& st);

    void PrintLine() const ;
};

#endif