// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
implementation file for the galaxy derived class
*/

#include "Galaxy.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

Galaxy::Galaxy(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
const ObservationSymmetricError<double>& in_magnitude,const ObservationString& in_morph, const ObservationSymmetricError<double>& in_mass
,const ObservationSymmetricError<double>& in_diamter)
: BaseAstronomicalObject(i_name,i_type,i_notes,in_coords,in_proper_motion,in_ang_size,in_parallax,in_redshift,
in_distance,in_magnitude)
{
  morphological_class = in_morph;
  mass = in_mass;
  diameter = in_diamter;
} 

Galaxy::Galaxy(BaseAstronomicalObject in_astro,const ObservationString& in_morph, const ObservationSymmetricError<double>& in_mass
,const ObservationSymmetricError<double>& in_diamter)
:BaseAstronomicalObject(in_astro.get_name(),in_astro.get_obj_type(),in_astro.get_notes(),in_astro.get_coords(),
in_astro.get_proper_motion(),in_astro.get_angular_size(),in_astro.get_parallax(),in_astro.get_red_shift(),
in_astro.get_distance(),in_astro.get_magnitude())
{
  morphological_class = in_morph;
  mass =in_mass;
  diameter = in_diamter;
}

// Member functions 

std::string Galaxy::return_formmated_file_string() const
{
  std::string temp_str = BaseAstronomicalObject::return_formmated_file_string();
  temp_str = temp_str + "," + morphological_class.return_obs_formatted_file_string() + "," + mass.return_obs_formatted_file_string();
  temp_str = temp_str + "," + diameter.return_obs_formatted_file_string();
  return temp_str;
}


void Galaxy::print_basic_information() const 
{
  BaseAstronomicalObject::print_basic_information();
  morphological_class.print_observation();
  std::cout<<'\n';
  mass.print_observation();
  std::cout<<'\n';
  diameter.print_observation();
  std::cout<<'\n';
}