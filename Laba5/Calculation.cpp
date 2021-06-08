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
double Calculation::calculate(Node* n)
{
    double a, b, c;
    if (n != nullptr)
    {
        if (isOperator(n->get_inside()))
        {
            a = calculate(n->get_left());
            b = calculate(n->get_right());
            switch (n->get_inside()[0])
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
        }
        else
        {
            c = stod(n->get_inside());
        }
        return c;
    }
}