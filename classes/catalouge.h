#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

class Catalouge
{
private:
protected:

bool has_file = false;
std::string file_name;

struct catalouge_obj
{

    int a;
};

std::vector<std::unique_ptr<catalouge_obj>> catalouge_items;

    
public:

Catalouge(){};
~Catalouge();
Catalouge(std::string input_file_name);

void change_file_name(std::string in_file_name);
bool check_if_file_provided();
void set_file_name();
void read_file();
void cli_wirte_to_file();
void write_file(std::string to_write);

std::string get_file_name() const {return file_name;}

void output_data();
void cli_output_data();
};