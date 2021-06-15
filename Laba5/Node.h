#pragma once
#include <string>

//implementation of tree with nodes
class Node
{
private:
    Node* left;
    Node* right;
    std::string inside;
    int counter;

public:
    Node()
    {
        left = nullptr;
        right = nullptr;
        inside = '\0';
        counter = 0;
    }
    Node(std::string ins)
    {
        left = nullptr;
        right = nullptr;
        inside = ins;
        if ((ins.length() > 2) or (isdigit(ins[0]) != 0) or (isalpha(ins[0]) != 0))
            counter = 2;
        else
            counter = 0;
    }
    Node(Node* l, Node* r, std::string ins = "\0")
    {
        left = l;
        right = r;
        inside = ins;
        counter = 0;
    }

    Node* get_left() { return left; }
    Node* get_right() { return right; }
    std::string get_inside() { return inside; }
    int get_counter() { return counter; }

    void set_left(Node* l) { left = l; }
    void set_right(Node* r) { right = r; }
    void set_inside(std::string ins) { inside = ins; }
    void set_counter(int a) { counter = a; }
};

