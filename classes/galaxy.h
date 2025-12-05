// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
Header file for the derived galaxy astronomical object
*/

#pragma once

#include "BaseAstronomicalObject.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Galaxy : public BaseAstronomicalObject
{
protected:
  ObservationString morphological_class; //Standard way that galaxy shapes are classified by astronomers
  ObservationSymmetricError<double> mass;
  ObservationSymmetricError<double> diameter; //Diameter as opposed to radius as galaxy sizes are typically given by diameter

public:
  Galaxy() = default;
  ~Galaxy() override  = default; //Overriding the virtual desctructor
  Galaxy(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
  const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
  const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
  const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
  const ObservationSymmetricError<double>& in_magnitude,const ObservationString& in_morph, const ObservationSymmetricError<double>& in_mass
  ,const ObservationSymmetricError<double>& in_diamter); 

  //Special constructor overload which takes in a base astronomical object input to allow the parser functions to be reused.
  Galaxy(BaseAstronomicalObject in_astro,const ObservationString& in_morph, const ObservationSymmetricError<double>& in_mass
  ,const ObservationSymmetricError<double>& in_diamter);

  // Set and get methods

  const ObservationString& get_morphological_class() const {return morphological_class;}
  const ObservationSymmetricError<double> get_mass() const {return mass;}
  const ObservationSymmetricError<double> get_diameter() const {return diameter;}

  void set_morphological_class(const ObservationString& in_morph){ morphological_class = in_morph;}
  void set_mass(const ObservationSymmetricError<double> in_mass){ mass = in_mass;}
  void set_diameter(const ObservationSymmetricError<double> in_diameter){diameter = in_diameter;}

  std::string return_formmated_file_string() const override;
  void print_basic_information() const override;

};
