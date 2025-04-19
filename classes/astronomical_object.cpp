#include <string>
#include <exception>


#include "astronomical_object.h"

/*--Constructors&Necessary functions--*/

AstronomicalObject::AstronomicalObject(const std::string& in_name,const int& in_obs_id, const double& in_ra,
const double& in_ra_err,const double& in_dec,const double& in_dec_error,const double& in_parallax,const double& in_prop_mot_ra,
const double& in_prop_mot_dec,const double& in_radial_velocity,const double& in_red_shift,const double& in_distance,
const double& in_distance_err,const double& in_apparent_mag,const std::string& in_notes)
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

std::string AstronomicalObject::formated_storage_string()
{
    std::string temp_string;
    std::cout<<"tempstring"<<temp_string<<std::endl;
    return temp_string;
}