#pragma once
#include <string>
#include "Node.h"

class Calculation
{
private:
    Node* root;
    double result;

    bool isOperator(std::string);

    bool isOperand(std::string);


    double pow(double a, double b);

    double calculate(Node* n);

public:
    Calculation(Node* r)
    {
        root = r;
        result = calculate(root);
    }

    double get_calculation()
    {
        return result;
    }
};

