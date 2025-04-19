#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>


#include "classes/astronomical_object.h"
#include "standard_tests/standard_input_validation.h"


int main()
{
    AstronomicalObject test("test",1,2,3,4,5);
    test.print_information();
    std::cout<<"Success"<<std::endl;
    int t{-1};
    std::cout<<is_positive(t)<<std::endl;
    return 0;
}