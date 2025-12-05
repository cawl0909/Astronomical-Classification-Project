// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
implementation file for the planet derived class
*/


#include "Planet.h"

/* Constructors */

Planet::Planet(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
const ObservationSymmetricError<double>& in_magnitude,const ObservationSymmetricError<double> in_mass,
const ObservationSymmetricError<double>& in_radius,const ObservationString& in_parent,const Orbit<double>& in_orbit)
: BaseAstronomicalObject(i_name,i_type,i_notes,in_coords,in_proper_motion,in_ang_size,in_parallax,in_redshift,
in_distance,in_magnitude)
{
  mass = in_mass;
  radius = in_radius;
  parent = in_parent;
  orbit = in_orbit;
}

Planet::Planet(const BaseAstronomicalObject& in_astro,const ObservationSymmetricError<double>& in_mass, ObservationSymmetricError<double>& in_radius,
const ObservationString& in_parent,const Orbit<double>& in_orbit)
:BaseAstronomicalObject(in_astro.get_name(),in_astro.get_obj_type(),in_astro.get_notes(),in_astro.get_coords(),
in_astro.get_proper_motion(),in_astro.get_angular_size(),in_astro.get_parallax(),in_astro.get_red_shift(),
in_astro.get_distance(),in_astro.get_magnitude())
{
  mass = in_mass;
  radius = in_radius;
  parent = in_parent;
  orbit = in_orbit;
}

const Orbit<double>& Planet::get_orbit() const
{
  return orbit;
}

void Planet::print_basic_information() const
{
  BaseAstronomicalObject::print_basic_information();
  mass.print_observation();
  std::cout<<'\n';
  radius.print_observation();
  std::cout<<'\n';
  parent.print_observation();
  std::cout<<'\n';
  orbit.print_observation();
  std::cout<<'\n';
}

std::string Planet::return_formmated_file_string() const 
{
  std::string temp_str = BaseAstronomicalObject::return_formmated_file_string() +","+mass.return_obs_formatted_file_string();
  temp_str = temp_str + "," +radius.return_obs_formatted_file_string() +"," + parent.return_obs_formatted_file_string();
  temp_str = temp_str +","+orbit.return_obs_formatted_file_string();
  return temp_str;
}