#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>


#include "../standard_tests/standard_input_validation.h"


// This class is the abstract base class for all astronomical objects 
// This contains the observational data corresponding to astronomical objects not their intrinsic qualities
// like the mass etc.



class AstronomicalObject
{
    private:
    bool empty = true;
    protected:

    //sentinal value of 0 for the errors is used if non is given as these are optional 

    std::string astro_obj_name;

    int obs_id;

    double right_ascension; //degrees 0-360
    double right_ascension_error; 

    double declination;//degrees -90-90
    double declination_error;

    double parallax;//mili-arcseconds

    double proper_motion_ra; //mili-arcseconds
    double proper_motion_dec;

    double radial_velcoity; //km^-s

    double red_shift_z; //number

    double distance; //lightyear
    double distance_error;

    double apparent_magnitude; //number

    std::string notes{"Empty"};

    public:

    AstronomicalObject(){}; //Default
    ~AstronomicalObject() = default; //Destructor
    AstronomicalObject(const std::string& in_name,const int& in_obs_id, const double& in_ra,const double& in_ra_err,
    const double& in_dec,const double& in_dec_error,const double& in_parallax,const double& in_prop_mot_ra,
    const double& in_prop_mot_dec,const double& in_radial_velocity,const double& in_red_shift,const double& in_distance,
    const double& in_distance_err,const double& in_apparent_mag,const std::string& in_notes);

    double get_right_ascension() const {return right_ascension;}
    double get_right_ascension_error() const {return right_ascension_error;}
    double get_declination() const {return declination;}
    double get_declination_error() const {return declination_error;}
    double get_distance() const {return distance;}
    double get_distance_error() const {return distance_error;}
    double get_apparent_magnitude() const {return apparent_magnitude;}
    const std::string& get_name() const {return astro_obj_name;}

    //void set_right_ascension(const double in_right_ascension);
    //void set_right_ascension_error(const double in_right_ascension_error);
    //void set_declination(const double in_declination);
    //void set_declination_error(const double in_declination_error);
    //void set_distance(const double in_distance);
    //void set_distance_error(const double in_distance_error);
    //void set_apparent_magnitude(const double in_apparent_magnitude);
//
    virtual std::string formated_storage_string();
    
    virtual void print_information();
};

//This class is for objects that  are not treated as pointer sources i.e. galaxies.
