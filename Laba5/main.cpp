#include <iostream>
#include "Parser.h"
#include "FileRead.h"
#include "Calculation.h"
#include "Constructor.h"

int main()
{
    std::string infix;
    FileRead fromfile("input.txt");

    Parser parced(fromfile.get_statement(), fromfile.get_pairs());    
    Constructor constr;

    constr.construct(parced.get_parsed_statement(), parced.get_num());
    Calculation calculated(constr.get_root());
    
    std::cout << "Result = " << calculated.get_calculation() << std::endl;
}

