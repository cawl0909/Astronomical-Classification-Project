#pragma once

#include <string>

//This file contains some standard tests used across most/all of the classes

//implmentating template in header

template <typename comparator>
bool is_positive(comparator input)
{
    return (input>=0) ? true : false;
}

template <typename boundtype>
bool is_within_bounds(boundtype input, boundtype bot_bound, boundtype top_bound)
{
    return ((input>=bot_bound)&&(input<=top_bound)) ? true : false;
}

bool is_non_zero_length(std::string test_string);

void test();

