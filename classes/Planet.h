// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
header file for the planet derived class
*/

#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <optional>

#include "observation/CombinedObservations.h"
#include "BaseAstronomicalObject.h"

class Planet : public BaseAstronomicalObject
{
protected:
  ObservationSymmetricError<double> mass;
  ObservationSymmetricError<double> radius;
  ObservationString parent;
  Orbit<double> orbit;
public:
  Planet() = default;
  ~Planet() = default;
  Planet(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
  const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
  const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
  const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
  const ObservationSymmetricError<double>& in_magnitude,const ObservationSymmetricError<double> in_mass,
  const ObservationSymmetricError<double>& in_radius,const ObservationString& in_parent,const Orbit<double>& in_orbit);

  Planet(const BaseAstronomicalObject& in_astro,const ObservationSymmetricError<double>& in_mass, ObservationSymmetricError<double>& in_radius,
  const ObservationString& in_parent,const Orbit<double>& in_orbit);

  /* Accessor functions */
  const ObservationSymmetricError<double>& get_mass() const {return mass;}
  const ObservationSymmetricError<double>& get_radius() const {return radius;}
  const Orbit<double>& get_orbit() const;
  const ObservationString& get_parent() const {return parent;}

  void print_basic_information() const override;
  std::string return_formmated_file_string() const override;
};