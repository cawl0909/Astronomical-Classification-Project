// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
This header file contains the base astronomical observed object, from this all the *observed* object classes
i.e. Star, Galaxy etc. are  derived from. 
*/

#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <exception>
#include <array>
#include <map>

#include "../standard_tests/standard_input_validation.h"
#include "observation/CombinedObservations.h"

static const std::vector<std::string> valid_obj_types = {"galaxy","star","planet","nebula","base"}; 

class BaseAstronomicalObject
{
protected:

  std::string obj_name; //This is the main common name used for this goes off SIMBAD 

  std::string obj_type; //Type of the object

  ObservationErrorEllipse<double> obj_coord; //object co-ordinate

  ObservationErrorEllipse<double> prop_motion; //propermotion can be 0 i.e. fixed w.r.t timescale/distance of obj, Sentinal val =0

  AngularSize<double> angular_size; //The angular size of the observation can be pointlike i.e distance star. Sentinal value = 0

  ObservationSymmetricError<double> parallax;//For very distant object this is 0 again hear to provide compatability with close by objects

  ObservationSymmetricError<double> red_shift; //redshift and radial velocity;

  ObservationTwoSidedError<double> distance; //light years

  ObservationSymmetricError<double> magnitude; // magnitude of the light

  std::string notes; //Short optional note on the object.

  std::map<std::string,std::shared_ptr<BaseObservation>> observations; //contains a map of all the observations
public:

  BaseAstronomicalObject() = default; //Just want to be explicity declare for clartiy
  virtual ~BaseAstronomicalObject() = default; //Destructors are handled automatically but want to virtualise so when using polymorphism the derived classes are cleaned up properly
  BaseAstronomicalObject(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
  const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
  const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
  const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
  const ObservationSymmetricError<double>& in_magnitude); // 

  /*Set and get interface methods */
  const std::string& get_name() const {return obj_name;}
  const std::string& get_obj_type() const {return obj_type;}
  const ObservationErrorEllipse<double>& get_coords() const {return obj_coord;}
  const ObservationErrorEllipse<double>& get_proper_motion() const {return prop_motion;}
  const AngularSize<double>& get_angular_size() const {return angular_size;}
  const ObservationSymmetricError<double>& get_parallax() const {return parallax;}
  const ObservationSymmetricError<double>& get_red_shift() const {return red_shift;}
  const ObservationTwoSidedError<double>& get_distance() const {return distance;}
  const ObservationSymmetricError<double>& get_magnitude() const {return magnitude;}
  const std::string& get_notes() const {return notes;}

  void set_name(const std::string& in_name){(is_empty_or_whitespace(in_name)) ? throw std::runtime_error("invald_string") : obj_name = in_name;}
  void set_obj_type(const std::string& in_type){(is_empty_or_whitespace(in_type) == true || is_within_set<std::string>(in_type,valid_obj_types) == false) ? throw std::runtime_error("no_valid_obj_type_provided") : obj_type = in_type;}
  void set_coords(const ObservationErrorEllipse<double>& in_coords){obj_coord = in_coords;}
  void set_proper_motion(const ObservationErrorEllipse<double>& in_prop_motion){prop_motion = in_prop_motion;}
  void set_angular_size(const AngularSize<double>& in_angular_size){angular_size = in_angular_size;}
  void set_parallax(const ObservationSymmetricError<double>& in_prallax){parallax = in_prallax;}
  void set_red_shift(const ObservationSymmetricError<double>& in_red_shift_velocity){red_shift = in_red_shift_velocity;}
  void set_distance(const ObservationTwoSidedError<double>& in_distance){distance = in_distance;}
  void set_magnitude(const ObservationSymmetricError<double>& in_magnitude){magnitude = in_magnitude;}
  void set_notes(const std::string& in_notes){is_empty_or_whitespace(in_notes) ?  throw(std::runtime_error("no_notes_provided")) : notes = in_notes;}

  /* Observations IO  */

  void add_observation(std::shared_ptr<BaseObservation> obs_ptr); //requires ptr to be passed so as to not lose information
  const BaseObservation& get_observation(std::string in_id); //returns the observation at index casted as the baseobs class

  void print_observation(std::string in_id) const; //prints observation at the index given in the observations
  void print_observations() const; // prints all the additional observations if there are any

  std::vector<std::string> return_observation_file_strings(); //returns a vector of formmated file strings for the observations

  /* File IO */
  virtual std::string return_formmated_file_string() const; //creates a correctly formatted storage csv string of the current object

  /* Visualisation  of basic information */
  virtual void print_basic_information() const; //prints all the basic (not additional observation) information
  void print_all_information() const; //combines basic infro+individual observation
};
