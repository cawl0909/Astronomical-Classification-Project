// Name: Awwab Butt ID: 11091269 Date: 5/4/2025
//Description:
/*
This header file contains the derived object definition for a string observation like the sspectral class 
*/

#pragma once

#include "baseobservation.h"


class ObservationString : public BaseObservation
{
protected:
  std::string information;
public:
  ObservationString() = default;
  ~ObservationString() = default;
  ObservationString(const std::string& i_id, const std::string& i_type, const std::string& i_ref, const std::string& i_info)
  :BaseObservation(i_id,i_type,i_ref)
  {
    is_empty_or_whitespace(i_info) ? throw std::runtime_error("no_information_provided") : information = i_info;
  }

  // Set&get methods

  const std::string& get_info() const {return information;}

  void set_info(const std::string& in_info){is_empty_or_whitespace(in_info) ? throw std::runtime_error("no_information_provided") : information = in_info;}

  void print_observation() const override
  {
    BaseObservation::print_observation();
    std::cout<<"Information: "<<information<<std::endl;
  }

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_str = BaseObservation::return_obs_formatted_file_string();
    temp_str = temp_str + "," +information;
    return temp_str;
  }
};