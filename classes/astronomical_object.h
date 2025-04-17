#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../standard_tests/standard_input_validation.h"


// This class is the fundemental base class for all astronomical objects 


class AstronomicalObject
{
    //This is for a point like object
    private:

    protected:

    std::string astro_obj_name;

    double right_ascension;
    double right_ascension_error;

    double declination;
    double declination_error;

    double distance;
    double distance_error;

    double apparent_magnitude;

    //decided to have magnitude as part of the base class since the vast majority of objects are detected by light
    //except exoplanets via transits etc.
    //instead of complicating the the class structure by having a bunch of classes for luminous objects.
    //the memory impact is minute and trivial to remedy if ever that comes up (probably never)

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

    std::string get_name() const {return astro_obj_name;}

    void set_right_ascension(const double in_right_ascension) {right_ascension =  in_right_ascension;}

    std::string return_formated_string();
    void print_information();
};

//This class is for objects that  are not treated as pointer sources i.e. galaxies.

class AstronomicalObjectNonPoint : public AstronomicalObject
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



