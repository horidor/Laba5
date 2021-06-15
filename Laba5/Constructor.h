#pragma once
#include <string>
#include "Node.h"

class Constructor
{
private:
    Node* root;

    Node* add_new(std::string);

    bool isOperator(std::string);

    bool isOperand(std::string);



    Node* construct_tree(std::string, Node*);
    void print_Tree(Node* p, int level);
public:
    Constructor()
    {
        root = nullptr;
    }

    //constructing is done by adding all of the tokens
    Node* construct(std::string* out, int n)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            root = construct_tree(out[i], root);
        }
        //print_Tree(root, 1);
        return root;
    }

    Node* get_root() { return root; }
};

