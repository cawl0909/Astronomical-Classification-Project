#include <fstream>
#include <iostream>
#include <vector>


#include "classes/astronomical_object.h"
#include "classes/galaxy.h"
#include "classes/stellar_object.h"
#include "classes/systems.h"
#include "standard_tests/standard_input_validation.h"


int main()
{
    std::cout<<"Success"<<std::endl;
    int t{-1};
    std::cout<<is_positive(t)<<std::endl;
    test();
    return 0;
}