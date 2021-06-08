#pragma once
#include <string>
#include <vector>
#include "stack.h"

class Parser
{
private:
    std::string* parsed_statement;
    int num_of_tokens;

    void Copy(std::string*);

    std::string* parse(std::string);

    int num_of_elements(std::string);
    void sort_station(std::string*);
    void replace_variables(std::vector < std::pair < std::string, std::string>>, std::string*);

    char priority(char, char);
public:
    Parser(std::string statement, std::vector<std::pair<std::string, std::string>> variables)
    {
        num_of_tokens = num_of_elements(statement);
        std::string* A = parse(statement);
        replace_variables(variables, A);
        sort_station(A);

        delete[] A;
    }

    std::string* get_parsed_statement() { return parsed_statement; }
    int get_num() { return num_of_tokens; }

    ~Parser()
    {
        delete[] parsed_statement;
    }
};

