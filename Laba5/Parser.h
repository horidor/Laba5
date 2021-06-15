#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "stack.h"

class Parser
{
private:
    std::string* parsed_statement;
    int num_of_tokens;

    void Copy(std::string*);

    std::string* parse(std::string);

    bool isOperand(std::string ch);

    int num_of_elements(std::string);
    void sort_station(std::string*);

    void output_parsed();

    char priority(char, char);
public:
    Parser(std::string statement, std::vector<std::pair<std::string, std::string>> variables)
    {
        num_of_tokens = num_of_elements(statement);
        std::string* A = parse(statement);

        sort_station(A);
        //output_parsed();
        delete[] A;
    }

    std::string* get_parsed_statement() { return parsed_statement; }
    int get_num() { return num_of_tokens; }

    ~Parser()
    {
        delete[] parsed_statement;
    }
};

