// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This header file contains the base observation class implementation.
*/

#include "BaseObservation.h"

BaseObservation::BaseObservation(const std::string& i_id, const std::string& i_type, const std::string& i_ref)
{
  is_empty_or_whitespace(i_id) ? throw std::runtime_error("no_id_provided") : obs_id = i_id;
  is_empty_or_whitespace(i_ref) ? throw std::runtime_error("no_reference_provided") : obs_ref = i_ref;
  if(i_ref == "n/a")
  {
    obs_ref = i_ref;
  }
  else if(i_ref.length() != 19)
  {
    throw std::runtime_error("reference_must_follow_the_bibcode_standard");
  }
  (is_empty_or_whitespace(i_type) == true || is_within_set<std::string>(i_type,valid_observation_types) == false) ? throw std::runtime_error("no_valid_obs_type_provided") : obs_type = i_type;
}

std::string BaseObservation::return_obs_formatted_file_string() const
{
  std::string temp_string;
  temp_string = temp_string + obs_type + "," + obs_id + "," + obs_ref;
  return temp_string;
}