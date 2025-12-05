// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
Header file for the derived star astronomical object
*/

#pragma once

#include "BaseAstronomicalObject.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Star : public BaseAstronomicalObject
{
protected:

  ObservationString spectral_class; //Morgan-Keenan typically, spectral classifcation of the star 
  ObservationSymmetricError<double> mass; //Solar masses
  ObservationSymmetricError<double> radius; //Solar radiaii
  ObservationSymmetricError<double> luminosity; //solar luminosities
  ObservationSymmetricError<double> effective_temp; //kelvin # The equivelent blackody temp that would produce like a star

  bool has_orbit;

public:
  Star() = default; // For clartiy
  ~Star() override = default; // Overriding the virtualised destructor from the base class

  //Paramterised constructor
  Star(const std::string& i_name, const std::string& i_type, const std::string& i_notes, 
  const ObservationErrorEllipse<double>& in_coords,const ObservationErrorEllipse<double>& in_proper_motion,
  const AngularSize<double>& in_ang_size, const ObservationSymmetricError<double>& in_parallax,
  const ObservationSymmetricError<double>& in_redshift,const ObservationTwoSidedError<double>& in_distance,
  const ObservationSymmetricError<double>& in_magnitude,const ObservationString& in_spectral_class, const
  ObservationSymmetricError<double>& in_mass, const ObservationSymmetricError<double>& in_radius,
  const ObservationSymmetricError<double>& in_luminosity, const ObservationSymmetricError<double>& in_e_temp);

  //Paramterised constructor but intakes a BaseAstronomicalObject class, this is to prevent code duplication for the parsers when
  //creating a Star object.
  Star(const BaseAstronomicalObject& in_astro,const ObservationString& in_spectral_class, const
  ObservationSymmetricError<double>& in_mass, const ObservationSymmetricError<double>& in_radius,
  const ObservationSymmetricError<double>& in_luminosity, const ObservationSymmetricError<double>& in_e_temp);

  // Set and get interface
  void set_spectral_class(const ObservationString& in_spectral_class){spectral_class = in_spectral_class;}
  void set_mass(const ObservationSymmetricError<double>& in_star_mass){mass = in_star_mass;}
  void set_radius(const ObservationSymmetricError<double>& in_radius){radius = in_radius;}
  void set_effective_temperature(const ObservationSymmetricError<double>& in_eff_temp){effective_temp = in_eff_temp;}
  void set_luminosity(const ObservationSymmetricError<double>& in_luminosity){luminosity = in_luminosity;}

  const ObservationString& get_spectral_class() const {return spectral_class;}
  const ObservationSymmetricError<double>& get_mass() const {return mass;}
  const ObservationSymmetricError<double>& get_radius() const {return radius;}
  const ObservationSymmetricError<double>& get_effective_temperature() const {return effective_temp;}
  const ObservationSymmetricError<double>& get_luminosity() const {return luminosity;}


  //Overriding the base class versions
  std::string return_formmated_file_string() const override;
  void print_basic_information() const override;
  
};
