// Name: Awwab Butt ID: 11091269 Date: 5/4/2025
//Description:
/*
This header file contains the derived object definition for a single error observation
*/

#pragma once

#include "baseobservation.h"

template <typename T> class ObservationSymmetricError : public BaseObservation
{
private:
  void print_observation_sub(std::string units) const
  {
    std::cout<<"Value("<< units <<"): " << std::scientific <<value << " | +/-: " << std::scientific << value_error<<std::endl;
  }
protected:
  T value;
  T value_error;
public:
  ObservationSymmetricError() = default;
  ~ObservationSymmetricError() = default;
  ObservationSymmetricError(const std::string& i_id, const std::string& i_type, const std::string& i_ref,T i_val,T i_val_err)
  : BaseObservation(i_id,i_type,i_ref)
  {
    if(i_type == "mass" || i_type == "distance" || i_type == "radius" || i_type  ==  "diameter" || i_type ==  "luminosity" || i_type == "effectivetemp")
    {
      is_positive(i_val)  ? value =  i_val : throw std::runtime_error(""+i_type+"_must_be_positive");
    }
    else
    {
      value = i_val;
    }
    value_error = i_val_err;
  }

  T get_obs_val() const {return value;}
  T get_obs_val_err() const {return value_error;}

  void set_obs_val(T i_val){value = i_val;}
  void set_obs_val_err(T i_val_err){value_error = i_val_err;}

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_string = BaseObservation::return_obs_formatted_file_string();
    temp_string = temp_string + "," + std::to_string(value) + "," + std::to_string(value_error);
    return temp_string;
  }
  void print_observation() const override
  {
    BaseObservation::print_observation();
    if(obs_type == "parallax")
    {
      print_observation_sub("mas");
    }
    else if(obs_type == "mass")
    {
      print_observation_sub("kg");
    }
    else if(obs_type =="diameter")
    {
      print_observation_sub("ly");
    }
    else if(obs_type == "effectivetemp")
    {
      print_observation_sub("K");
    }
    else if(obs_type == "luminosity")
    {
      print_observation_sub("Lo");
    }
    else if(obs_type == "radius")
    {
      print_observation_sub("m");
    }
    else 
    {
      print_observation_sub("");
    }
  }
};