// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
Implementation for the star class header file
*/


#include "Star.h"

#include <string>
#include <vector>
#include <iostream>

/* Constructors */

Star::Star(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
const ObservationSymmetricError<double>& in_magnitude,const ObservationString& in_spectral_class, const
ObservationSymmetricError<double>& in_mass, const ObservationSymmetricError<double>& in_radius,
const ObservationSymmetricError<double>& in_luminosity, const ObservationSymmetricError<double>& in_e_temp)
: BaseAstronomicalObject(i_name,i_type,i_notes,in_coords,in_proper_motion,in_ang_size,in_parallax,in_redshift,
in_distance,in_magnitude)
{
  spectral_class = in_spectral_class;
  mass = in_mass;
  radius = in_radius;
  luminosity = in_luminosity;
  effective_temp = in_e_temp;
}


Star::Star(const BaseAstronomicalObject& in_astro,const ObservationString& in_spectral_class, const
ObservationSymmetricError<double>& in_mass, const ObservationSymmetricError<double>& in_radius,
const ObservationSymmetricError<double>& in_luminosity, const ObservationSymmetricError<double>& in_e_temp)
:BaseAstronomicalObject(in_astro.get_name(),in_astro.get_obj_type(),in_astro.get_notes(),in_astro.get_coords(),
in_astro.get_proper_motion(),in_astro.get_angular_size(),in_astro.get_parallax(),in_astro.get_red_shift(),
in_astro.get_distance(),in_astro.get_magnitude())
{
  spectral_class = in_spectral_class;
  mass = in_mass;
  radius = in_radius;
  luminosity = in_luminosity;
  effective_temp = in_e_temp;
}

/* Member functions */

void Star::print_basic_information() const
{
  BaseAstronomicalObject::print_basic_information();
  spectral_class.print_observation();
  std::cout<<'\n';
  mass.print_observation();
  std::cout<<'\n';
  radius.print_observation();
  std::cout<<'\n';
  luminosity.print_observation();
  std::cout<<'\n';
  effective_temp.print_observation();
  std::cout<<'\n';
}

std::string Star::return_formmated_file_string() const
{
  std::string temp_string;
  temp_string = temp_string + BaseAstronomicalObject::return_formmated_file_string();
  temp_string = temp_string + "," + spectral_class.return_obs_formatted_file_string();
  temp_string = temp_string +","+ mass.return_obs_formatted_file_string() + "," + radius.return_obs_formatted_file_string();
  temp_string = temp_string + "," + luminosity.return_obs_formatted_file_string() + "," + effective_temp.return_obs_formatted_file_string();
  return temp_string;
}


