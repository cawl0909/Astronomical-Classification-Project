// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This header file contains the angular size observation class.
*/

#pragma once

#include "BaseObservation.h"

template <typename T> class AngularSize : public BaseObservation
{
protected:
  //defines ellipse with error
  T major_axis;
  T major_axis_err;
  T minor_axis;
  T minor_axis_err;
  T pos_angle; //position angle in degrees 0-360
  T pos_angle_err;
public:
  ~AngularSize() = default;
  AngularSize() = default;
  AngularSize(const std::string& i_id, const std::string& i_type, const std::string& i_ref,T i_maj_ax,T i_maj_ax_err,T i_min_axis,T i_min_axis_err,T i_pa,T i_pa_err)
  : BaseObservation(i_id,i_type,i_ref)
  {
    if(is_positive(major_axis) && is_positive(minor_axis) && is_within_bounds<double>(pos_angle,0,360)) //checks if the axes are within the bounds
    {
      major_axis = i_maj_ax; 
      major_axis_err = i_maj_ax_err;
      minor_axis = i_min_axis;
      minor_axis_err = i_min_axis_err;
      pos_angle = i_pa;
      pos_angle_err = i_pa_err;
    }
    else
    {
      throw std::runtime_error("angular_sizes_must_be_positive");
    }
  }

  T get_obs_major_axis() const {return major_axis;}
  T get_obs_major_axis_err() const {return major_axis_err;}
  T get_obs_minor_axis() const {return minor_axis;}
  T get_obs_minor_axis_err() const {return minor_axis_err;}
  T get_obs_pos_angle() const {return pos_angle;}
  T get_obs_pos_angle_err() const {return pos_angle_err;}

  void set_obs_major_axis(T i_maj){is_positive(i_maj) ?  major_axis = i_maj : throw std::runtime_error("major_axis_must_be_positive");}
  void set_obs_major_axis_err(T i_maj_err){major_axis = i_maj_err;}
  void set_obs_minor_axis(T i_min){is_positive(i_min) ?  minor_axis = i_min : throw std::runtime_error("minor_axis_must_be_positive");}
  void set_obs_minor_axis_err(T i_min_err){minor_axis_err = i_min_err;}
  void set_obs_pos_angle(T i_pos){is_positive(i_pos) ?  pos_angle = i_pos : throw std::runtime_error("position_angle_must_be_positive");}
  void set_obs_pos_angle_err(T i_pos_err){pos_angle_err = i_pos_err;}

  std::string return_obs_formatted_file_string() const override
  {
    std::string temp_string = BaseObservation::return_obs_formatted_file_string();
    temp_string = temp_string + "," + std::to_string(major_axis) + "," + std::to_string(major_axis_err) + "," + std::to_string(minor_axis)
    + "," + std::to_string(minor_axis_err) + "," + std::to_string(pos_angle) + "," + std::to_string(pos_angle_err);
    return temp_string;
  }
  void print_observation() const override
  {
    BaseObservation::print_observation(); 
    std::cout<<"Major-axis(mas): " << std::scientific << (major_axis) << " | +/-: " << std::scientific << (major_axis_err) <<
    " | Minor-axis(mas): " << std::scientific << (minor_axis) << " | +/-: " << std::scientific << (minor_axis_err) <<
    " | Position angle(deg): " << std::scientific << (pos_angle) << " | +/-: " << std::scientific << (pos_angle_err)<<std::endl;;
  }
};
