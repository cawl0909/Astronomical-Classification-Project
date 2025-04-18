#include <string>
#include <exception>


#include "astronomical_object.h"

AstronomicalObject::AstronomicalObject(std::string in_name, double in_ra, double in_ra_err, double in_dec, double in_dec_err, double distance, double distance_err,double in_app_mag)
{
    apparent_magnitude = in_app_mag;
    if(is_non_zero_length(in_name) == true)
    {
        astro_obj_name =  in_name;
    }
    else
    {
        std::cout<<"The astronomical object must have name"<<std::endl;
        throw "no_name";
    }
    if (is_positive(in_ra) && is_positive(in_ra_err))
    {
        right_ascension = in_ra;
        right_ascension_error = in_ra_err;
    }
    else
    {
        std::cout<<"Right asscension must be positive"<<std::endl;
        throw "not_positive";
    }
}