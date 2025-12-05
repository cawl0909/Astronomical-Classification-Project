// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This header file contains the base orbit object definition
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "BaseObservation.h"

template <typename T> class Orbit : public BaseObservation
{
protected:
  T eccentricity;
  T semi_major_axis;
  T orbital_period;

public:

  Orbit() = default;
  ~Orbit() = default;
  Orbit(const std::string& i_id, const std::string& i_type, const std::string& i_ref, T in_e,
  T in_sma, T in_op)
  : BaseObservation(i_id,i_type,i_ref)
  {
    if(is_positive(in_sma) && is_positive(in_op) && is_positive(in_e))
    {
      semi_major_axis = in_sma;
      orbital_period = in_op;
      eccentricity = in_e;
    }
    else
    {
      throw std::runtime_error("orbital_paramters_must_be_positive");
    }
  }

  T get_eccentricity() const {return eccentricity;}
  T get_semi_major_axis() const {return semi_major_axis;}
  T get_orbital_perioid() const {return orbital_period;}

  void set_eccentricity(T in_e){ eccentricity = in_e;}
  void set_semi_major_axis(T in_sma){semi_major_axis = in_sma;}
  void set_orbital_period(T in_op){orbital_period = in_op;}

  /* Override base functions*/
  void print_observation() const override
  {
    BaseObservation::print_observation();
    std::cout<<"Semi-major axis(m): "<<semi_major_axis<<" | Eccentricity: "<<eccentricity<<" | Orbital Period(days): "<<orbital_period<<std::endl;
  }

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_str = BaseObservation::return_obs_formatted_file_string();
    temp_str = temp_str + ","+std::to_string(semi_major_axis)+","+std::to_string(eccentricity)+","+std::to_string(orbital_period);
    return temp_str;
  }

};