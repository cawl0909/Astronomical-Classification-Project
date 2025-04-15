#pragma once
#include <string>
#include <vector>
#include <iostream>

// This class is the fundemental base class for all astronomical objects 
// Uses the SIMBAD standard

class AstronomicalObject
{
    private:

    protected:

    std::string astro_obj_name;

    double right_ascension;
    double right_ascension_error;

    double declination;
    double declination_error;

    double distance;
    double distance_error;

    // 0 angular size corresponds to point source

    double angular_size_ra;
    double angular_size_ra_error;

    double angular_size_d;
    double angular_size_d_error;

    public:

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

