#pragma once
#include <string>
#include "Node.h"
#include <vector>

class Calculation
{
private:
    Node* root;
    double result;
    std::vector<std::pair<std::string, std::string>> variables;

    bool isOperator(std::string);

    bool isOperand(std::string);


    double pow(double a, double b);

    double calculate_expression(double a, std::string op, double b);

    double getOperand(std::string operand);

    double getVariable(std::string variable);

    double calculate(Node* n);

public:
    Calculation(Node* r, std::vector<std::pair<std::string, std::string>> variables)
    {
        root = r;
        this->variables = variables;
        result = calculate(root);
    }

    double get_calculation()
    {
        return result;
    }
};

