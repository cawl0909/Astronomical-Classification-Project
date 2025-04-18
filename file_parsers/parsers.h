#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

/* Reads a line and returns that as a string  */
std::string base_line_parse();
/* Iterates over all of the lines of the file and outputs an string vector contaning all the line elements*/
std::vector<std::string> parse_file_lines(std::string fname);
/**/