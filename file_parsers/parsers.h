// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
// Description:
/*
This file is the header file for the file parser functions
They take in an input string, tokenize it and then parse it, creating the relevant observation object
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "../classes/BaseAstronomicalObject.h"
#include "../classes/observation/CombinedObservations.h"
#include "../classes/star.h"
#include "../classes/galaxy.h"
#include "../classes/planet.h"

std::vector<std::string> tokenizer(const std::string& input_string, char delim); // Converts a csv line string into a vector of 'tokens' of strings for further processing

// Parsers for the individual observation class types
ObservationErrorEllipse<double> parse_error_ellipse(const std::vector<std::string>& input_tokens, size_t index);
ObservationSymmetricError<double> parse_symmetric(const std::vector<std::string>& input_tokens, size_t index);
ObservationTwoSidedError<double> parse_two_sided(const std::vector<std::string>& input_tokens, size_t index);
AngularSize<double> parse_angular_size(const std::vector<std::string>& input_tokens, size_t index);
ObservationString parse_string_obs(const std::vector<std::string>& input_tokens, size_t index);
Orbit<double> parse_orbit_obs(const std::vector<std::string>& input_tokens, size_t index);

// Parsers to create the astronomical object classes
// These essentially collect the together the parsers seen above and implemenet them for the specific astronomical object
BaseAstronomicalObject make_base_astronomical_object(const std::vector<std::string>& tokenized_input);
Star make_star_object(const std::vector<std::string>& tokenized_input);
Galaxy make_galaxy_object(const std::vector<std::string>& tokenized_input);
Planet make_planet_object(const std::vector<std::string>& tokenized_input);
