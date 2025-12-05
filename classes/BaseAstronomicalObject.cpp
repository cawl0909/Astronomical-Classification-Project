// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This implementation file for the base astronomical astronomical object
*/

#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <algorithm>

#include "BaseAstronomicalObject.h"


/* Constructors&Necessary functions */


BaseAstronomicalObject::BaseAstronomicalObject(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
const ObservationSymmetricError<double>& in_magnitude)
{
  is_empty_or_whitespace(i_notes) ?  throw(std::runtime_error("no_notes_provided")) : notes = i_notes;
  is_empty_or_whitespace(i_name) ? throw(std::runtime_error("no_name_provided")) : obj_name = i_name;
  (is_empty_or_whitespace(i_type) == true || is_within_set<std::string>(i_type,valid_obj_types) == false) ? throw std::runtime_error("no_valid_type_provided") : obj_type = i_type; 
  parallax = in_parallax;
  obj_coord = in_coords;
  prop_motion = in_proper_motion;
  angular_size = in_ang_size;
  red_shift = in_redshift;
  distance = in_distance;
  magnitude = in_magnitude;
}

/* Member functions */

void BaseAstronomicalObject::print_basic_information() const 
{
  std::cout<<"|-----------------------------------------------------------------------|"<<std::endl;
  std::cout<<obj_type+" "+obj_name + " basic information, has "<<observations.size()<<" extra observations :"<<std::endl;
  std::cout<<'\n';
  obj_coord.print_observation();
  std::cout<<'\n';
  prop_motion.print_observation();
  std::cout<<'\n';
  angular_size.print_observation();
  std::cout<<'\n';
  parallax.print_observation();
  std::cout<<'\n';
  red_shift.print_observation();
  std::cout<<'\n';
  distance.print_observation();
  std::cout<<'\n';
  magnitude.print_observation();
  std::cout<<'\n';
  std::cout<<"Notes: "<<notes<<std::endl;
  std::cout<<'\n';
}

std::string BaseAstronomicalObject::return_formmated_file_string() const
{
  std::string temp_str;
  temp_str = obj_type + "," + obj_name;
  temp_str = temp_str + "," + obj_coord.return_obs_formatted_file_string() + "," + prop_motion.return_obs_formatted_file_string();
  temp_str = temp_str + "," + angular_size.return_obs_formatted_file_string() + "," + parallax.return_obs_formatted_file_string();
  temp_str = temp_str + "," + red_shift.return_obs_formatted_file_string() + "," + distance.return_obs_formatted_file_string();
  temp_str = temp_str + "," + magnitude.return_obs_formatted_file_string()+",notes"+","+notes;
  return temp_str;
}

/* Observation functions */

const BaseObservation& BaseAstronomicalObject::get_observation(std::string in_id)
{
  auto obs = observations.find(in_id);
  if(obs == observations.end())
  {
    throw  std::runtime_error("obs_not_found");
  }
  else
  {
    return *observations[obs->first];
  }
}

std::vector<std::string> BaseAstronomicalObject::return_observation_file_strings()
{
  std::vector<std::string> obs_vector;
  if(observations.size() == 0)
  {
    return obs_vector;
  }
  else
  {
    for(const auto& x : observations)
    {
      std::string temp_str = obj_name +","+x.second->return_obs_formatted_file_string();
      obs_vector.push_back(temp_str);
    }
  }
  return obs_vector;
}


void BaseAstronomicalObject::add_observation(std::shared_ptr<BaseObservation> obs_ptr)
{
  bool found = false;
  if(observations[obs_ptr->get_obs_id()])
  { 
    throw std::runtime_error("obs_id_already_exists");
  }
  else
  {
    observations[obs_ptr->get_obs_id()] = obs_ptr;
  }
}

void BaseAstronomicalObject::print_observation(std::string in_id) const
{
  std::cout<<"Printing observation ID: "<<in_id<<std::endl;
  auto obs = observations.find(in_id);
  if(obs == observations.end())
  {
    std::cout<<"No object of that ID exists"<<std::endl;
  }
  else
  {
    obs->second->print_observation();
  }
}

void BaseAstronomicalObject::print_observations() const
{
  std::cout<<"There are "<< observations.size() << " observations" <<std::endl;
  int obs_size = observations.size();
  if(obs_size == 0)
  {
    return;
  }
  for(const auto& x : observations)
  {
    x.second->print_observation();
    std::cout<<"\n";
  }
}

void BaseAstronomicalObject::print_all_information() const
{
  print_basic_information();
  print_observations();
}

