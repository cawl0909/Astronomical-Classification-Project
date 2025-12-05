// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
// Description:
/*
This file is the header file for the file parser functions
They take in an input string, tokenize it and then parse it, creating the relevant observation object or AstronomicalObject
and then return it
*/

#include "parsers.h"

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <exception>

std::vector<std::string> tokenizer(const std::string& input_string, char delim)
{
  /* Creates some temporary variables and iterates through the stringstream finding all the strings between the delimiter, typically ","
  it then adds these to a vector until the end of the string stream is reached and returns a vector of 'token' strings */

  std::vector<std::string> tokens;
  std::stringstream stream(input_string);
  std::string temp;
  while (std::getline(stream, temp, delim))
  {
    tokens.push_back(temp);
  }
  return tokens;
}

// These are the individual observation type paraser implementations, they are easy to the understand. Read the tokens, covert to the correct data type and return an object of that type
// In the future I want to convert these to templates to allow for more modualirty but the string to numerical type conversions were hard to figure out how to do for an arbritrary type T

ObservationErrorEllipse<double> parse_error_ellipse(const std::vector<std::string>& input_tokens, size_t index)
{
  std::string temp_type = input_tokens[index]; // already parsed this so guaranteed to hold this;
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    double ra = std::stod(input_tokens[index + 3]);
    double dec = std::stod(input_tokens[index + 4]);
    double maj_axis = std::stod(input_tokens[index + 5]);
    double min_axis = std::stod(input_tokens[index + 6]);
    double pa = std::stod(input_tokens[index + 7]);
    ObservationErrorEllipse<double> temp(temp_id, temp_type, temp_ref, ra, dec, maj_axis, min_axis, pa);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
}

ObservationSymmetricError<double> parse_symmetric(const std::vector<std::string> &input_tokens, size_t index)
{
  std::string temp_type = input_tokens[index];
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    double value = std::stod(input_tokens[index + 3]);
    double err = std::stod(input_tokens[index + 4]);
    ObservationSymmetricError<double> temp(temp_id, temp_type, temp_ref, value, err);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
}

ObservationTwoSidedError<double> parse_two_sided(const std::vector<std::string> &input_tokens, size_t index)
{

  std::string temp_type = input_tokens[index];
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    double value = std::stod(input_tokens[index + 3]);
    double val_top_err = std::stod(input_tokens[index + 4]);
    double val_bot_err = std::stod(input_tokens[index + 5]);
    ObservationTwoSidedError<double> temp(temp_id, temp_type, temp_ref, value, val_top_err, val_bot_err);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
}

AngularSize<double> parse_angular_size(const std::vector<std::string> &input_tokens, size_t index)
{
  std::string temp_type = input_tokens[index];
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    double maj = std::stod(input_tokens[index + 3]);
    double maj_err = std::stod(input_tokens[index + 4]);
    double min = std::stod(input_tokens[index + 5]);
    double min_err = std::stod(input_tokens[index + 6]);
    double pa = std::stod(input_tokens[index + 7]);
    double pa_err = std::stod(input_tokens[index + 8]);
    AngularSize<double> temp(temp_id, temp_type, temp_ref, maj, maj_err, min, min_err, pa, pa_err);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
}

ObservationString parse_string_obs(const std::vector<std::string> &input_tokens, size_t index)
{
  std::string temp_type = input_tokens[index];
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    std::string information = input_tokens[index + 3];
    ObservationString temp(temp_id, temp_type, temp_ref, information);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
};

Orbit<double> parse_orbit_obs(const std::vector<std::string> &input_tokens, size_t index)
{
  std::string temp_type = input_tokens[index];
  try
  {
    std::string temp_id = input_tokens[index + 1];
    std::string temp_ref = input_tokens[index + 2];
    double eccentricity = std::stod(input_tokens[index + 3]);
    double semi_major_axis = std::stod(input_tokens[index + 4]);
    double orbital_period = std::stod(input_tokens[index + 5]);
    Orbit<double> temp(temp_id, temp_type, temp_ref, eccentricity, semi_major_axis, orbital_period);
    return temp;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("failed_to_parse_" + temp_type);
  }
}

/*This creates the base astronomical object from the tokenized input
it has a {variable}_p flags to check if it has been provided as they are neccesary. If it has successfully parsed all the
data needed it returns a base astronomical object. The 'observations'  are empty and the shared pointers automatically delete
themselves so there is no need to worry about a memory leak */
BaseAstronomicalObject make_base_astronomical_object(const std::vector<std::string> &tokenized_input)
{
  std::string obj_type = tokenized_input[0];
  std::string obj_name = tokenized_input[1];
  std::string obj_notes;
  bool notes_p = false; // varaible name + _p for provided shorthand
  ObservationErrorEllipse<double> temp_coord;
  bool coords_p = false; // provided check
  ObservationErrorEllipse<double> temp_prop_motiom;
  bool prop_p = false;
  AngularSize<double> temp_angular;
  bool ang_p = false;
  ObservationSymmetricError<double> temp_mag;
  bool mag_p = false;
  ObservationSymmetricError<double> temp_parallax;
  bool parallax_p = false;
  ObservationSymmetricError<double> temp_red_shift;
  bool redshift_p = false;
  ObservationTwoSidedError<double> temp_distance;
  bool distance_p = false;
  for (size_t i = 0; i < tokenized_input.size(); i++)
  {
    if (tokenized_input[i] == "coordinates")
    {
      temp_coord = parse_error_ellipse(tokenized_input, i);
      coords_p = true;
    }
    else if (tokenized_input[i] == "proper_motion")
    {
      temp_prop_motiom = parse_error_ellipse(tokenized_input, i);
      prop_p = true;
    }
    else if (tokenized_input[i] == "angular_size")
    {
      temp_angular = parse_angular_size(tokenized_input, i);
      ang_p = true;
    }
    else if (tokenized_input[i] == "parallax")
    {
      temp_parallax = parse_symmetric(tokenized_input, i);
      parallax_p = true;
    }
    else if (tokenized_input[i] == "redshift")
    {
      temp_red_shift = parse_symmetric(tokenized_input, i);
      redshift_p = true;
    }
    else if (tokenized_input[i] == "distance")
    {
      temp_distance = parse_two_sided(tokenized_input, i);
      distance_p = true;
    }
    else if (tokenized_input[i] == "magnitude")
    {
      temp_mag = parse_symmetric(tokenized_input, i);
      mag_p = true;
    }
    else if (tokenized_input[i] == "notes")
    {
      obj_notes = tokenized_input[i + 1];
      notes_p = true;
    }
  }

  if ((coords_p && prop_p && ang_p && parallax_p && redshift_p && distance_p && mag_p && notes_p) == true)
  {
    BaseAstronomicalObject test_obj(obj_name, obj_type, obj_notes, temp_coord, temp_prop_motiom, temp_angular, temp_parallax, temp_red_shift, temp_distance, temp_mag);
    return test_obj;
  }
  else
  {
    throw std::runtime_error("not_all_required_data_fields_were_provided");
  }
}

/* Star csv parser */
/* Simillar to the astronomical object parser but foor the Star class, it takes a base astro class as an input aswell*/
Star make_star_object(const std::vector<std::string> &tokenized_input)
{
  BaseAstronomicalObject baseastroobj = make_base_astronomical_object(tokenized_input); // Extends the base parser
  ObservationString spectral_class;
  bool spectral_class_p = false; // varaible name + p for provided shorthand to check if provided
  ObservationSymmetricError<double> mass;
  bool mass_p = false;
  ObservationSymmetricError<double> radius;
  bool radius_p = false;
  ObservationSymmetricError<double> effective_temp;
  bool etemp_p = false;
  ObservationSymmetricError<double> luminosity;
  bool luminosity_p = false;
  for (size_t i = 0; i < tokenized_input.size(); i++)
  {
    if (tokenized_input[i] == "spectral_class")
    {
      spectral_class = parse_string_obs(tokenized_input, i);
      spectral_class_p = true;
    }
    else if (tokenized_input[i] == "radius")
    {
      radius = parse_symmetric(tokenized_input, i);
      radius_p = true;
    }
    else if (tokenized_input[i] == "luminosity")
    {
      luminosity = parse_symmetric(tokenized_input, i);
      luminosity_p = true;
    }
    else if (tokenized_input[i] == "mass")
    {
      mass = parse_symmetric(tokenized_input, i);
      mass_p = true;
    }
    else if (tokenized_input[i] == "effectivetemp")
    {
      effective_temp = parse_symmetric(tokenized_input, i);
      etemp_p = true;
    }
  }
  if ((etemp_p && mass_p && luminosity_p && radius_p && spectral_class_p) == true)
  {
    Star tempstar(baseastroobj, spectral_class, mass, radius, luminosity, effective_temp);
    return tempstar;
  }
  else
  {
    throw std::runtime_error("not_all_required_data_fields_were_provided");
  }
}

Galaxy make_galaxy_object(const std::vector<std::string> &tokenized_input)
{
  BaseAstronomicalObject base_obj = make_base_astronomical_object(tokenized_input);
  ObservationString morph_class;
  bool morph_class_p = false;
  ObservationSymmetricError<double> mass;
  bool mass_p = false;
  ObservationSymmetricError<double> diameter;
  bool diameter_p = false;
  for (size_t i = 0; i < tokenized_input.size(); i++)
  {
    if (tokenized_input[i] == "morphological_class")
    {
      morph_class = parse_string_obs(tokenized_input, i);
      // std::cout<<"yes1"<<std::endl;
      morph_class_p = true;
    }
    else if (tokenized_input[i] == "mass")
    {
      mass = parse_symmetric(tokenized_input, i);
      // std::cout<<"yes2"<<std::endl;
      mass_p = true;
    }
    else if (tokenized_input[i] == "diameter")
    {
      diameter = parse_symmetric(tokenized_input, i);
      // std::cout<<"yes3"<<std::endl;
      diameter_p = true;
    }
  }
  if ((mass_p && diameter_p && morph_class_p) == true)
  {
    Galaxy tempgalaxy(base_obj, morph_class, mass, diameter);
    return tempgalaxy;
  }
  else
  {
    throw std::runtime_error("not_all_required_fields_provided");
  }
}

Planet make_planet_object(const std::vector<std::string> &tokenized_input)
{
  BaseAstronomicalObject base_obj = make_base_astronomical_object(tokenized_input);

  ObservationSymmetricError<double> radius;
  bool rardius_p = false;
  ObservationSymmetricError<double> mass;
  bool mass_p = false;
  Orbit<double> orbit;
  bool orbit_p = false;
  ObservationString parent;
  bool parent_p = false;
  for (size_t i = 0; i < tokenized_input.size(); i++)
  {
    if (tokenized_input[i] == "mass")
    {
      mass = parse_symmetric(tokenized_input, i);
      mass_p = true;
    }
    else if (tokenized_input[i] == "radius")
    {
      radius = parse_symmetric(tokenized_input, i);
      rardius_p = true;
    }
    else if (tokenized_input[i] == "orbit")
    {
      orbit = parse_orbit_obs(tokenized_input, i);
      orbit_p = true;
    }
    else if (tokenized_input[i] == "parent")
    {
      parent = parse_string_obs(tokenized_input, i);
      parent_p = true;
    }
  }
  if ((mass_p && rardius_p && orbit_p && parent_p) == true)
  {
    Planet tempplanet(base_obj, mass, radius, parent, orbit);
    return tempplanet;
  }
  else
  {
    throw std::runtime_error("not_all_required_fields_provided");
  }
}