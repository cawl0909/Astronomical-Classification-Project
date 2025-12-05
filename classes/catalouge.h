// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
The catalouge class acts as the main interface between the user and the backend class data structure
Contains two main components: The file parser and the CLI user interface for adding/getting information
*/

#pragma once

#include "BaseAstronomicalObject.h"
#include "star.h"
#include "galaxy.h"
#include "Planet.h"
#include "../file_parsers/parsers.h"
#include "../projection/projection.h"

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>

class Catalouge
{
private:

	std::map<std::string,std::shared_ptr<BaseAstronomicalObject>> catalouge_map; 

public:

	//Basic constructor/destructors

	Catalouge(){};
	~Catalouge() = default;

	// Interface functionss
	const BaseAstronomicalObject& get_object(const std::string& obj_name);

	std::vector<std::string> get_catalouge_keys(); //returns a vector of the keys (names) in the catalouge

	void remove_object(const std::string& obj_name);

	void add_object_string(const std::string& object_line); //adds the object corresponding to the formmated string.
	void add_object(std::shared_ptr<BaseAstronomicalObject> in_object);

	void add_observation(std::shared_ptr<BaseObservation> in_obs,const std::string& obj_name);
	void add_observation_string(const std::string& observation_line);

	/* File I/O */

	void read_file(const std::string& in_file_name);
	void export_file(const std::string& file_name, const std::vector<std::string>& selection);
	void make_projection_selection(std::vector<std::string> selection,std::string file_name);
	/* CLI helper functions friend and members depending on the context*/

	void open_cli_interface(); //main function that starts the cli
	void print_catalouge_names(const std::string& type);
	void print_report();
};