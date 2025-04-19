#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>


#include "../standard_tests/standard_input_validation.h"


// This class is the fundemental base class for all astronomical objects 
// This contains the observational data corresponding to astronomical objects not their intrinsic qualities
// like the mass etc.

struct CatalougeIdentifierPair
{
    std::string survey_name;
    std::string identifier;
};

class AstronomicalObject
{
    private:
    bool empty = true;
    protected:

    std::string astro_obj_name;

    double right_ascension; //mili-arcseconds
    double right_ascension_error;

    double declination;//mili-arcseconds
    double declination_error;

    double parallax;//mili-arcseconds

    double proper_motion_ra; //mili-arcseconds
    double proper_motion_dec;

    double radial_velcoity; //km^-s

    double red_shift_z; //number

    double distance; //lightyear
    double distance_error;

    double apparent_magnitude; //number
    double absolute_magnitude;

    std::string notes{"Empty"};

    public:

    AstronomicalObject(){}; //Default
    ~AstronomicalObject() = default; //Destructor
    AstronomicalObject(std::string in_name, double in_ra, double in_ra_err, double in_dec, double in_dec_err, double distance, double distance_err,double in_app_mag);

    double get_right_ascension() const {return right_ascension;}
    double get_right_ascension_error() const {return right_ascension_error;}
    double get_declination() const {return declination;}
    double get_declination_error() const {return declination_error;}
    double get_distance() const {return distance;}
    double get_distance_error() const {return distance_error;}
    double get_apparent_magnitude() const {return apparent_magnitude;}
    double get_absolute_magnitude() const {return absolute_magnitude;}

    std::string get_name() const {return astro_obj_name;}

    void set_right_ascension(const double in_right_ascension);
    void set_right_ascension_error(const double in_right_ascension_error);
    void set_declination(const double in_declination);
    void set_declination_error(const double in_declination_error);
    void set_distance(const double in_distance);
    void set_distance_error(const double in_distance_error);
    void set_apparent_magnitude(const double in_apparent_magnitude);
    void set_absolute_magnitude(const double in_absolute_magnitude);

    std::string formated_storage_string();

    void print_information();
};

//This class is for objects that  are not treated as pointer sources i.e. galaxies.

class NonPointAstronomicalObject : public AstronomicalObject
{
    private:
    protected:

    double apparent_size_major_axis;
    double apparent_size_major_axis_error;
    double apparent_size_minor_axis;
    double apparent_size_minor_axis_error;

    public:

    double get_apparent_size_major_axis() const {return apparent_size_major_axis;}
    double get_apparent_size_major_axis_error() const {return apparent_size_major_axis_error;}
    double get_apparent_size_minor_axis() const {return apparent_size_minor_axis;}
    double get_apparent_size_minor_axis_error() const {return apparent_size_minor_axis_error;}

};




