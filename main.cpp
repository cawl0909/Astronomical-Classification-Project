#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>


#include "classes/astronomical_object.h"
#include "standard_tests/standard_input_validation.h"


int main()
{
    AstronomicalObject test("test",1,2,3,4,3,1,2,3,4,5,6,7,8,"10");
    test.print_information();
    std::string test2 = test.formated_storage_string();
    std::cout<<"Success"<<std::endl;
    int t{-1};
    std::cout<<is_positive(t)<<std::endl;
    return 0;
}