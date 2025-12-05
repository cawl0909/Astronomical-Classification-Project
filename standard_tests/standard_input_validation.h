// Name: Awwab Butt ID: 11091269 Date: 05/5/2025
//Description:
/*
Header file for a bunch of standard input validation functions used across the project
*/


#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

//This file contains some standard tests used across most/all of the classes

//implmentating template in header


template <typename comparator> bool is_positive(comparator input)
{
  return (input>=0) ? true : false;
}


template <typename boundtype> bool is_within_bounds(boundtype input, boundtype bot_bound, boundtype top_bound)
{
  return ((input>=bot_bound)&&(input<=top_bound)) ? true : false;
}

bool is_non_zero_length(std::string test_string);

bool is_empty_or_whitespace(const std::string& input);


template <typename T> bool is_within_set(const T& value, const std::vector<T>& set)
{
    typename std::vector<T>::const_iterator it = std::find(set.begin(), set.end(), value);
    return it != set.end();
}