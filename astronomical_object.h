#pragma once
#include <string>
#include <vector>
#include <iostream>

// This class is the fundemental base class for all astronomical objects 
// 

class astronomical_obect
{
    private:

    protected:

    std::string astro_obj_name;
    double right_ascension;
    double declination;

    public:

    double get_right_ascension() const {return right_ascension;}
    double get_declination() const {return declination;}
    std::string get_name() const {return astro_obj_name;}

    void set_right_ascension(const double in_right_ascension) {right_ascension =  in_right_ascension;}
};