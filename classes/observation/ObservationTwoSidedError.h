// Name: Awwab Butt ID: 11091269 Date: 5/4/2025
//Description:
/*
This header file contains the derived object definition for a two sideded error observation
*/

#pragma once

#include "BaseObservation.h"

template <typename T> class ObservationTwoSidedError : public BaseObservation
{
private:
  void print_observation_sub(std::string units) const
  {
    std::cout<<"Value("<<units<<"): " << std::scientific << value << " | +: " << std::scientific << value_err_top << " | -: " << std::scientific << value_err_bot<<std::endl;
  }
protected:
  T value;
  T value_err_top;
  T value_err_bot;
public:
  ObservationTwoSidedError() = default;
  ~ObservationTwoSidedError() = default;
  ObservationTwoSidedError(const std::string& i_id, const std::string& i_type, const std::string& i_ref,T i_val, T i_val_err_top, T i_val_err_bot)
  :BaseObservation(i_id,i_type,i_ref)
  {
    if(i_type == "distance")
    {
      is_positive(i_val) ? value = i_val : throw std::runtime_error(i_type+"_must_be_positive");
    }
    else
    {
      value = i_val;
    }
    value_err_top = i_val_err_top;
    value_err_bot = i_val_err_bot;
  }

  T get_obs_value() const {return value;}
  T get_obs_value_err_top() const {return value_err_top;}
  T get_obs_value_err_bot() const {return value_err_bot;}

  void set_obs_val(T i_val){value = i_val;}
  void set_obs_err_top(T i_val_t_err){value_err_top = i_val_t_err;}
  void set_obs_err_bot(T i_val_t_bot){value_err_bot = i_val_t_bot;}

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_string = BaseObservation::return_obs_formatted_file_string();
    temp_string = temp_string + "," + std::to_string(value) + "," +  std::to_string(value_err_top) + "," + std::to_string(value_err_bot);
    return temp_string;
  }
  virtual void print_observation() const override
  {
    BaseObservation::print_observation();
    if(obs_type == "distance")
    {
      print_observation_sub("ly");
    }
    else
    {
      print_observation_sub("");
    }
  }
};