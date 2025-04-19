#include <string>
#include <exception>


#include "astronomical_object.h"

/*--Constructors&Necessary functions--*/

AstronomicalObject::AstronomicalObject(const std::string& in_name,const int& in_obs_id, const double& in_ra,
const double& in_ra_err,const double& in_dec,const double& in_dec_error)
{
    astro_obj_name =  in_name;
    obs_id = in_obs_id;
    right_ascension =  in_ra;
    right_ascension_error = in_ra_err;
    declination = in_dec;
    declination_error =  in_dec_error;
}

/*--Functions--*/

void AstronomicalObject::print_information()
{
    std::cout<<"Astronomical Object Name: "<<astro_obj_name<<" Observation ID: "<<obs_id<<std::endl;
    std::cout<<"RA: "<<right_ascension<<" RAErr: "<<right_ascension_error<<" Dec: "<<declination<<" DecErr: "<<declination_error<<std::endl;

}
