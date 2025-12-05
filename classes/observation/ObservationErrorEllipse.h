// Name: Awwab Butt ID: 11091269 Date: 5/4/2025
//Description:
/*
This header file contains the derived object definition for an error ellipse 
*/

#pragma once

#include "BaseObservation.h"

template <typename T> class ObservationErrorEllipse : public BaseObservation
{
private:
  void print_observation_sub(std::string units) const
  {
    std::cout<<"Right ascension(" +units+"): " << std::scientific << value_ra << " | Declination("+units+"): "
    << std::scientific << value_dec << " | Error ellipse | Major-axis(mas): " << std::scientific << major_axis <<
    " | Minor-axis(mas): " << std::scientific <<  (minor_axis) << " | Position angle(deg): " << std::scientific << (pos_angle)<<std::endl;
  }
protected:
  T value_ra;
  T value_dec;
  T major_axis;
  T minor_axis;
  T pos_angle;
public:
  ObservationErrorEllipse() = default;
  ~ObservationErrorEllipse() override = default;
  ObservationErrorEllipse(const std::string& i_id, const std::string& i_type, const std::string& i_ref,T i_ra,T i_dec, T i_ma_axis, T i_min_axis, T i_pa)
  :BaseObservation(i_id,i_type,i_ref)
  {
      if(obs_type == "coordinates")
      {
          if((is_within_bounds<T>(i_ra,0,360)) && (is_within_bounds<T>(i_dec,-90.0,90.0)))
          {
              value_ra = i_ra;
              value_dec = i_dec;
              major_axis = i_ma_axis;
              minor_axis = i_min_axis;
              pos_angle = i_pa;
          }
          else
          {
              throw std::runtime_error("coords_not_valid");
          }
      }
      else
      {
          value_ra = i_ra;
          value_dec = i_dec;
          major_axis = i_ma_axis;
          minor_axis = i_min_axis;
          pos_angle = i_pa;
      }
  }

  T get_obs_ra() const {return value_ra;}
  T get_obs_dec() const {return value_dec;}
  T get_obs_maj_axis() const {return major_axis;}
  T get_obs_min_axis() const {return minor_axis;}
  T get_obs_pa() const {return pos_angle;}

  void set_obs_ra(T i_ra){value_ra = i_ra;}
  void set_obs_dec(T i_dec){value_dec = i_dec;}
  void set_obs_maj_axis(T i_maj){major_axis = i_maj;}
  void set_obs_min_axis(T i_min){minor_axis = i_min;}
  void set_obs_pa(T i_pa){pos_angle = i_pa;}

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_string = BaseObservation::return_obs_formatted_file_string();
    temp_string = temp_string + "," + std::to_string(value_ra) + "," + std::to_string(value_dec) + "," + std::to_string(major_axis)
    + "," + std::to_string(minor_axis) + "," + std::to_string(pos_angle);
    return temp_string;
  }
  void print_observation() const override
  {
    BaseObservation::print_observation();
    if(obs_type == "coordinates")
    {
      print_observation_sub("deg");
    }
    else if(obs_type == "proper_motion")
    {
      print_observation_sub("mas/yr");
    }
    else
    {
      print_observation_sub("");
    }
  }
};
