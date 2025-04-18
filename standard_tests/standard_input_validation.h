#pragma once

#include <string>

//This file containss some standard tests used across most/all of the classes

//implmentating template in header

template <typename comparator>
bool is_positive(comparator input)
{
    if(input >= 0)
    {
        return true;
    }
    return false;
}

bool is_non_zero_length(std::string test_string);

void test();

