// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This header file contains the base observation class from which the rest are derived
*/

#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../../standard_tests/standard_input_validation.h"

static const std::vector<std::string> valid_observation_types = {"distance","coordinates","proper_motion","parallax","orbit","parent",
"redshift","magnitude","unknown","angular_size","radius","mass","effectivetemp","luminosity","spectral_class","diameter","morphological_class"};

class BaseObservation
{
protected:
  std::string obs_id; //observation id
  std::string obs_type; //type of observation
  std::string obs_ref; //observation reference use the bibcode standard
public:
  BaseObservation() = default;
  BaseObservation(const std::string& i_id, const std::string& i_type, const std::string& i_ref);
  virtual ~BaseObservation() = default;

  const std::string& get_obs_id() const {return obs_id;}
  const std::string& get_obs_type() const {return obs_type;}
  const std::string& get_obs_ref() const {return obs_ref;}

  void set_obs_type(const std::string& i_type){(is_empty_or_whitespace(i_type) == true || is_within_set<std::string>(i_type,valid_observation_types) == false) ? throw std::runtime_error("no_valid_obs_type_provided") : obs_type = i_type;}
  void set_obs_id(const std::string& i_id){is_empty_or_whitespace(i_id) ? throw std::runtime_error("no_id_provided") : obs_id = i_id;}
  void set_obs_ref(const std::string& i_ref){is_empty_or_whitespace(i_ref) ? throw std::runtime_error("no_reference_provided") : obs_ref = i_ref;}

  virtual std::string return_obs_formatted_file_string() const;
  virtual void print_observation() const {std::cout<<obs_type+" Data | Observation ID: " + obs_id + " | Reference: " +obs_ref<<std::endl;}
};