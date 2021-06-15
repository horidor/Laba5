#include "Parser.h"
#include <iostream>

bool Parser::isOperand(std::string ch)
{
    if ((ch.length() > 1) or (isdigit(ch[0]) != 0) or (isalpha(ch[0]) != 0))
        return true;
    else
        return false;
}

int Parser::num_of_elements(std::string S) //getting number of elements from the file
{
    int count_el = 0;
    bool flag = true;
    for (int i = 0; i < S.length(); i++)
    {
        switch (S[i])
        {
        case '+':
        case '/':
        case '^':
        case '*':
        case '(':
        case ')':
            flag = true;
            count_el++;
            break;
        case '-':
            if (i == 0)
                ;
            else if (S[i - 1] == '(')
                ;
            else
            {
                count_el++;

            }
            flag = true;
            break;
        default:
            if (flag)
            {
                count_el++;
                flag = false;
            }
        }
    }
    return count_el;
}

std::string* Parser::parse(std::string D) //dividing into operators and operands
{
    std::string* L = new std::string[num_of_tokens];
    int i = 0;
    int k = 0;
    int j = 0;
    if (D[0] == '-')
    {
        j = 1;
    }
    while (j < D.length())
    {
        if (((isdigit(D[j]) == 0) and ((isalpha(D[j])) == 0)) and (k - j == 0) and ((isdigit(D[j + 1]) != 0) or (isalpha(D[j + 1]) != 0)))
        {
            L[i] = D.substr(j, 1);
            k++;
            i++;
        }
        else if (((isdigit(D[j]) == 0) and (isalpha(D[j]) == 0)) and (D[j] == '(') and (D[j + 1] == '-'))
        {
            k = j;
            j += 2;
            L[i] = D.substr(k, 1);
            i++;
            k++;
            while ((isdigit(D[j]) != 0) or (isalpha(D[j]) != 0))
            {
                j++;
            }
            L[i] = D.substr(k, j - k);
            i++;
            k = j;
            if (D[j] == ')')
            {
                L[i] = D.substr(k, 1);
                j++;
                k++;
                i++;
            }
            if (j >= D.length())
            {
                return L;
            }

            L[i] = D.substr(k, 1);
            k++;
            i++;
        }
        else if ((isdigit(D[j]) == 0) and (isalpha(D[j]) == 0) and (D[j]!='.'))
        {
            L[i] = D.substr(k, j - k);
            k = j;
            i++;
            L[i] = D.substr(k, 1);
            i++;
            k++;
        }
        j++;
    }
    if (i < num_of_tokens)
    {
        L[i] = D.substr(k, j - k);
    }
    return L;
}

void Parser::sort_station(std::string* L) //Shunting-Yard algorithm
{
    int n = num_of_tokens;
    stack<char> ST;
    char l;
    std::string* out = new std::string[n];
    int i = 0;
    int j = 0;
    bool flag;
    while (j < n)
    {
        if (isOperand(L[j]))
        {
            out[i] = L[j];
            i++;
        }
        else
        {
            if ((L[j][0] != ')') and (L[j][0] != '('))
            {
                while (ST.check_pt() > -1)
                {
                    l = ST.pop();
                    if (l == '(')
                    {
                        ST.push(l);
                        break;
                    }
                    else if (priority(l, L[j][0]) == l)
                    {
                        out[i] = l;
                        i++;
                    }
                    else
                    {
                        ST.push(l);
                        break;
                    }
                }
                ST.push(L[j][0]);
            }
            else if (L[j][0] == '(')
            {
                ST.push(L[j][0]);
            }
            else if (L[j][0] == ')')
            {
                while (ST.check_pt() > -1)
                {
                    l = ST.pop();
                    if (l == '(')
                    {
                        num_of_tokens -= 2;
                        break;
                    }
                    out[i] = l;
                    i++;
                }
            }
        }
        j++;
    }
    while (ST.check_pt() > -1)
    {
        out[i] = ST.pop();
        i++;
    }
    std::string* parsed_statement = new std::string[num_of_tokens];
    Copy(out);
    delete[] out;
}

void Parser::output_parsed()
{
    for (int i = 0; i < num_of_tokens; i++)
    {
        std::cout << parsed_statement[i] << std::endl;
    }
    std::cout << std::endl;
}

void Parser::Copy(std::string* out)
{
    parsed_statement = new std::string[num_of_tokens];
    for (int i = 0; i < num_of_tokens; i++)
    {
        parsed_statement[i] = out[i];
    }
}

char Parser::priority(char a, char b) //priority check
{
    char a_n = ' ';
    char b_n = ' ';
    char PRIORITY_LIST[10] = { '^','2','*','1','/','1','+','0','-','0' };
    for (int i = 0; i < 10; i += 2)
    {
        if (a == PRIORITY_LIST[i])
        {
            a_n = PRIORITY_LIST[i + 1];
        }
        if (b == PRIORITY_LIST[i])
        {
            b_n = PRIORITY_LIST[i + 1];
        }
    }
    if (a_n > b_n)
    {
        return a;
    }
    else if ((a_n < b_n) or ((a_n == b_n) and (a == '^')))
    {
        return b;
    }
    else
    {
        return a;
    }
}