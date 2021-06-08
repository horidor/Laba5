#include "FileRead.h"


//making inputs from file more usable for programm
void FileRead::normalize()
{
    for (int i = 0; i < elnum - 1; i++)
    {
        buffer = input_from_file[i].substr(0, input_from_file[i].find(' ', 0));
        buffer += input_from_file[i].substr(input_from_file[i].find_last_of(' '));
        buffer.erase(buffer.length() - 1);
        input_from_file[i] = buffer;
    }
    input_from_file[elnum - 1].erase(input_from_file[elnum - 1].length() - 1);
    std::string a, b;
    for (int i = 0; i < elnum - 1; i++)
    {
        a = input_from_file[i].substr(0, input_from_file[i].find(' '));
        b = input_from_file[i].substr(input_from_file[i].find(' ') + 1);
        pairs.push_back(std::make_pair(a, b));
    }
}

//reading from file
FileRead::FileRead(std::string name)
{
    pFile.open(name, std::ios::in);
    int i = 0;
    while (!pFile.eof())
    {
        getline(pFile, buffer);
        input_from_file.push_back(buffer);
    }
    pFile.close();
    elnum = input_from_file.size();
    normalize();
}