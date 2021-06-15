#include "Constructor.h"
#include <iostream>


bool Constructor::isOperator(std::string ch)
{
    if ((ch.length() < 2) and ((isdigit(ch[0]) == 0) and (isalpha(ch[0]) == 0)))
        return true;
    else
        return false;
}

bool Constructor::isOperand(std::string ch)
{
    if ((ch.length() > 1) or (isdigit(ch[0]) != 0) or (isalpha(ch[0]) != 0))
        return true;
    else
        return false;
}

//
//
//          Construction of AST
//
//
//

//adds new nodes to the tree
Node* Constructor::add_new(std::string ins)
{
    Node* temp = new Node(ins);
    return temp;
}

//constructs tree recursively
Node* Constructor::construct_tree(std::string ins, Node* nova)
{
    Node* temp;
    if (nova == nullptr)
    {
        temp = add_new(ins);
    }
    else
    {
        if (isOperator(ins))
        {
            if (nova->get_right() == nullptr)
            {
                nova->set_right(construct_tree(ins, nova->get_right()));
            }
            else if (nova->get_right()->get_counter() < 2)
            {
                nova->set_right(construct_tree(ins, nova->get_right()));
            }
            else if (nova->get_right()->get_counter() >= 2)
            {
                nova->set_left(construct_tree(ins, nova->get_left()));
            }
            nova->set_counter(nova->get_counter() - 1);
        }
        else
        {
            if (nova->get_right() == nullptr)
            {
                nova->set_right(construct_tree(ins, nova->get_right()));
            }
            else if ((isOperator(nova->get_right()->get_inside())) and ((nova->get_right()->get_counter() < 2)))
            {
                nova->set_right(construct_tree(ins, nova->get_right()));
            }
            else
            {
                nova->set_left(construct_tree(ins, nova->get_left()));
            }
            nova->set_counter(nova->get_counter() + 1);
        }
        temp = nova;
    }
    return temp;
}

void Constructor::print_Tree(Node* p, int level)
{
    if (p)
    {
        print_Tree(p->get_left(), level + 1);
        for (int i = 0; i < level; i++) std::cout << "   ";
        std::cout << p->get_inside() << std::endl;
        print_Tree(p->get_right(), level + 1);
    }
}