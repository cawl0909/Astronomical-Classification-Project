#include "standard_input_validation.h"

#include<iostream>
#include<string>
#include<vector>



bool is_non_zero_length(std::string input)
{
    if(input.length() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool is_within_allowed_values(int r)
{
    return false;
}

void test()
{
    std::cout<<"Test"<<std::endl;
}