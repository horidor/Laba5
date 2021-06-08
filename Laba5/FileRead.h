#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class FileRead
{
private:
    std::fstream pFile;
    std::string buffer;
    std::vector<std::string> input_from_file;
    std::vector<std::pair< std::string, std::string>> pairs;
    int elnum;

    void normalize();
public:
    FileRead(std::string name);

    std::string get_statement() { return input_from_file[elnum - 1]; }
    std::vector<std::pair<std::string, std::string>> get_pairs() { return pairs; }



};

