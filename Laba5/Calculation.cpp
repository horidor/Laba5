#include "Calculation.h"

bool Calculation::isOperator(std::string ch)
{
    if ((ch.length() < 2) and ((isdigit(ch[0]) == 0) and (isalpha(ch[0]) == 0)))
        return true;
    else
        return false;
}

bool Calculation::isOperand(std::string ch)
{
    if ((ch.length() > 1) or (isdigit(ch[0]) != 0) or (isalpha(ch[0]) != 0))
        return true;
    else
        return false;
}


double Calculation::pow(double a, double b)
{
    if (b > 0)
    {
        return a * pow(a, b - 1);
    }
    else
    {
        return 1;
    }
}

//
//    calculating recursively - from left to right
//

double Calculation::calculate_expression(double a, std::string op, double b)
{
    double c;
    switch (op[0])
    {
    case '+':
        c = a + b;
        break;
    case '-':
        c = a - b;
        break;
    case '*':
        c = a * b;
        break;
    case '/':
        c = a / b;
        break;
    case '^':
        c = pow(a, b);
        break;
    }
    return c;
}

double Calculation::getOperand(std::string operand)
{
    if (isdigit(operand[0]) != 0)
        return stod(operand);
    else
        return getVariable(operand);
}

double Calculation::getVariable(std::string variable)
{
    for (int i = 0; i < variables.size(); i++)
    {
        if (variable == variables[i].first)
            return stod(variables[i].second);
    }
}

double Calculation::calculate(Node* n)
{
    double a, b, c;
    if (n != nullptr)
    {
        if (isOperator(n->get_inside()))
        {
            a = calculate(n->get_left());
            b = calculate(n->get_right());
            c = calculate_expression(a, n->get_inside(), b);
        }
        else
        {
            c = getOperand(n->get_inside());
        }
        return c;
    }
}