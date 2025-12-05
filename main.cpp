// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
main.cpp, from which all the rest of the files are called and ran.
Initiliases the CLI which is the main interface
*/

#include "classes/Catalouge.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

int main()
{
  Catalouge catalouge;
  //catalouge.read_file("test_datasets/data.txt");
  catalouge.open_cli_interface();
  return 0;
};