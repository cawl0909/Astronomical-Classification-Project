// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
implementation file for the non templated functions
*/

#include "standard_input_validation.h"

#include<iostream>
#include<string>
#include<vector>
#include<cstring>



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

bool is_empty_or_whitespace(const std::string& input)
{
  std::size_t check_empty = input.find_first_not_of(" ");
  if((input.empty() == true) || (check_empty == std::string::npos))
  {
    return true;
  }
  else
  {
    return false;
  }
  return false;
}

