// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
Implementation file for the catalouge class, mainly the FILE io and the internal IO component
*/
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <string>

#include "Catalouge.h"

/* interface functions */

void Catalouge::remove_object(const std::string& obj_name)
{
  if(is_empty_or_whitespace(obj_name)) //checks if name is given
  {
    throw std::runtime_error("no_object_name_provided");
  }
  if(catalouge_map[obj_name]) //if it exists it is removed
  {
    catalouge_map.erase(obj_name);
  }
  return;
}

const BaseAstronomicalObject& Catalouge::get_object(const std::string& obj_name)
{
  if(catalouge_map.find(obj_name) != catalouge_map.end())
  {
    return *catalouge_map[obj_name]; //finds the correspodning object and returns a derferenced ref
  }
  else
  {
    throw std::runtime_error("object_not_found");
  }
}

std::vector<std::string> Catalouge::get_catalouge_keys()
{
  std::vector<std::string> temp_keys;
  for(auto const& x : catalouge_map) //asdasd
  {
    temp_keys.push_back(x.first);
  }
  return temp_keys;
}

void Catalouge::add_object(std::shared_ptr<BaseAstronomicalObject> in_object)
{
  for(auto const& x : catalouge_map) //iterates through the map if the name is found throws an error else adds the object
  {
    if(x.second->get_name() == in_object->get_name())
    {
      throw std::runtime_error("object_of_that_name_already_exists");
    }
  }
  catalouge_map[in_object->get_name()] = in_object;
};

void Catalouge::add_observation(std::shared_ptr<BaseObservation> in_obs,const std::string& obj_name)
{
  if(catalouge_map[obj_name]) //same as above but for an observation ascoaited with an astro obj
  {
    catalouge_map[obj_name]->add_observation(in_obs);
  }
  else
  {
    throw std::runtime_error("object_of_that_name_doesnt_exist");
  }
}

/* Member Functions FILE IO */

void Catalouge::add_object_string(const std::string& object_line)
{
  if(is_empty_or_whitespace(object_line)) //checks if it is empty
  {
    throw std::runtime_error("empty_line_proivded");
    return;
  }
  std::vector<std::string> tokenized_input = tokenizer(object_line,','); //tokenizes the input string
  if((std::find(valid_obj_types.begin(),valid_obj_types.end(),tokenized_input[0]) != valid_obj_types.end()))
  {
    //parses the first item in the csv string and calls the corresponding parser.
    //once it is parsed, a sharedd ptr is created and then added to the map with the corresponding obj name
    std::string obj_type = tokenized_input[0]; 
    if(obj_type == "base")
    {
      catalouge_map[tokenized_input[1]] = std::make_shared<BaseAstronomicalObject>(make_base_astronomical_object(tokenized_input));
    }
    else if(obj_type == "star")
    {
      std::shared_ptr<Star> tempstar = std::make_shared<Star>(make_star_object(tokenized_input));
      catalouge_map[tokenized_input[1]] = tempstar;
    }
    else if(obj_type == "galaxy")
    {
      std::shared_ptr<Galaxy> tempgalaxy = std::make_shared<Galaxy>(make_galaxy_object(tokenized_input));
      catalouge_map[tokenized_input[1]] = tempgalaxy;
    }
    else if(obj_type == "planet")
    {
      std::shared_ptr<Planet> tempplanet = std::make_shared<Planet>(make_planet_object(tokenized_input));
      catalouge_map[tokenized_input[1]] = tempplanet;
    }
    else
    {
      throw std::runtime_error("valid_astro_obj_parser_could_not_be_found_for_type_specified");
    }
  }
  else
  {
    throw std::runtime_error("could_not_parse_as_an_astronomical_object");
  }
}

void Catalouge::add_observation_string(const std::string& observation_line)
{
  if(is_empty_or_whitespace(observation_line))
  {
    throw std::runtime_error("empty_line_proivded");
    return;
  }
  std::vector<std::string> tokenized_input = tokenizer(observation_line,',');
  if((std::find(valid_observation_types.begin(),valid_observation_types.end(),tokenized_input[1])) != valid_observation_types.end())
  {
    if(catalouge_map.find(tokenized_input[0]) == catalouge_map.end())
    {
      throw std::runtime_error("parent_object_doesnt_exist_for_observation");
    }
    std::string obs_type = tokenized_input[1];
    if(obs_type =="parallax" || obs_type == "redshift" || obs_type == "magnitude" || obs_type == "radius" || obs_type == "luminosity"|| obs_type == "effectivetemp" || obs_type == "mass")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<ObservationSymmetricError<double>>(parse_symmetric(tokenized_input,1)));
    }
    else if(obs_type == "coordinates" || obs_type == "proper_motion")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<ObservationErrorEllipse<double>>(parse_error_ellipse(tokenized_input,1)));
    }
    else if(obs_type == "distance")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<ObservationTwoSidedError<double>>(parse_two_sided(tokenized_input,1)));
    }
    else if(obs_type == "angular_size")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<AngularSize<double>>(parse_angular_size(tokenized_input,1)));
    }
    else if(obs_type == "spectral_class" || "parent" ||"spectral_class")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<ObservationString>(parse_string_obs(tokenized_input,1)));
    }
    else if(obs_type == "orbit")
    {
      catalouge_map[tokenized_input[0]]->add_observation(std::make_shared<Orbit<double>>(parse_orbit_obs(tokenized_input,1)));
    }
    else
    {
      throw std::runtime_error("failed_to_parse_obs");
    }
  }
  else
  {
    throw std::runtime_error("could_not_parse_as_obs");
  }
}


void Catalouge::read_file(const std::string& in_file_name)
{    
  std::ifstream file(in_file_name);
  if(file.is_open() == false)
  {
      std::cout<<"File failed to open"<<std::endl;
      return;
  }
  std::string file_line;
  int lnum = 0;
  while(std::getline(file,file_line))
  {
    lnum+=1;
    try
    {
      std::vector<std::string> tokenized_input = tokenizer(file_line,',');
      if((std::find(valid_obj_types.begin(),valid_obj_types.end(),tokenized_input[0]) != valid_obj_types.end()))
      {
        add_object_string(file_line);
      }
      else if((std::find(valid_observation_types.begin(),valid_observation_types.end(),tokenized_input[1])) != valid_observation_types.end())
      {
        add_observation_string(file_line);
      }
      else
      {
        throw std::runtime_error("no_valid_parse_for_string_provided_check_it_follows_the_correct_format");
      }
    }
    catch(const std::exception& e)
    {
      std::cerr <<"Failed to read line " << lnum <<'\n';
      std::cerr<<"Reason: " << e.what() << '\n';
    }
  }
  std::cout<<"Completed reading " <<in_file_name<<" file"<<std::endl;
  file.close();
}

void Catalouge::export_file(const std::string& file_name,const std::vector<std::string>& selection)
{
  if(file_name.length() <5)
  {
    std::cout<<"File name must be atleast one character, not including the extension"<<std::endl;
    return;
  }
  std::string extension = file_name.substr(file_name.length()-4,4);
  if(extension != ".csv" && extension != ".txt")
  {
    std::cout<<"The extension must be .txt or .csv"<<std::endl;
    return;
  }
  std::ofstream file(file_name);
  if(file.is_open() == false)
  {
    std::cout<<"File failed to open"<<std::endl;
    return;
  }
  for(size_t i = 0;i<selection.size();i++)
  {
    if(catalouge_map[selection[i]])
    {
      file << catalouge_map[selection[i]]->return_formmated_file_string() <<std::endl;
      std::vector<std::string> obsvector = catalouge_map[selection[i]]->return_observation_file_strings();
      for(size_t i = 0;i<obsvector.size();i++)
      {
        file << obsvector[i] << std::endl;
      }
    }
  }
  std::cout<<"Exported selection to "<<file_name<<std::endl;
  file.close();
}


