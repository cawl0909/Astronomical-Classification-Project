// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
//Description:
/*
Implementation file for the CLI component of the Catalouge class 
*/
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <string>

#include "Catalouge.h"

//CLI interface
template <typename T> void print_vector(const std::vector<T>& in_vector)
{
  for(size_t i = 0; i<in_vector.size();i++)
  {
    std::cout<<in_vector[i]<<" ";
  }
  std::cout<<std::endl;
}

void Catalouge::print_catalouge_names(const std::string& type = "all")
{
  if(is_within_set(type,valid_obj_types) == false && type != "all")
  {
    std::cout<<"The provided object type is not supported"<<std::endl;
    return;
  }
  for(auto const& x : catalouge_map) //iterates through the map, if it finds a name of a compatiable object it prints sit.
  {
    if(type == "all")
    {
      std::cout<<x.first<<" ";
    }
    else
    {
      if(x.second->get_obj_type() == type)
      {
        std::cout<<x.first<<" ";
      }
    }
  }
  std::cout<<std::endl; //ends the line
}

void Catalouge::make_projection_selection(std::vector<std::string> selection,std::string file_name)
{
  std::vector<std::vector<Pixel>> temp_pixels = make_base_ellipse();
  for(int i = 0; i<selection.size();i++)
  {
    if(catalouge_map[selection[i]])
    {
      add_object_to_projection(*catalouge_map[selection[i]],temp_pixels);
    }
  }
  draw_bmp(file_name,temp_pixels);
}

void Catalouge::print_report()
{
  int star_count{0};
  int galaxy_count{0};
  int planet_count{0};
  int base_count{0};
  BaseAstronomicalObject furthest;
  for(const auto& x : catalouge_map)
  {
    if(x.second->get_obj_type() == "star")
    {
      star_count+=1;
    }
    else if(x.second->get_obj_type() == "galaxy")
    {
      galaxy_count +=1;
    }
    else if(x.second->get_obj_type() == "planet")
    {
      planet_count +=1;
    }    
    else if(x.second->get_obj_type() == "base")
    {
      galaxy_count +=1;
    }
    ObservationTwoSidedError<double> temp_d = x.second->get_distance(); //gets the distance objects
    ObservationTwoSidedError<double> temp_df = furthest.get_distance();
    if(temp_d.get_obs_value() > temp_df.get_obs_value()) //if its further makes it the 'furthesst'
    {
      furthest = *x.second;
    }
  }
  std::cout<<"There are currently "<<catalouge_map.size()<<" objects stored in the catalouge."<<std::endl;
  std::cout<<star_count <<" Stars " << galaxy_count << " Galaxies "<<planet_count << " Planets " << base_count<< " other objects " <<std::endl;
  std::cout<<"The furthest object stored is "<<furthest.get_name()<<" at a distance of "<<(furthest.get_distance()).get_obs_value()<<"ly"<<std::endl;
}

static void print_help_information() //Static since its just an auxillary function in this file
{
  std::cout<<"Available commands: "<<std::endl;
  std::cout<<"exit - exits the CLI"<<std::endl;
  std::cout<<"h/help - prints a list of commands and descriptions, ? denotes an optional argument, / is or, [] denotes variable arguments like a file name"<<std::endl;
  std::cout<<"validobjtypes - prints a list of astronomical object types supported"<<std::endl;
  std::cout<<"validobstypes - prints a list of observation types supported"<<std::endl;
  std::cout<<"list [?type] - prints a list of the current objects stored can specify the type"<<std::endl;
  std::cout<<"print [name(s)]/(selection/all)- prints all the information for the object with the given name(s) multi name querys require comma seperated names"<<std::endl;
  std::cout<<"  print all - prints all the objects currently in the catalouge"<<std::endl;
  std::cout<<"  print selection - prints all the objects in the selection"<<std::endl;
  std::cout<<"selection [action] - performs various selection related commands, allows the user to specficy a selection on which to perform operation"<<std::endl;
  std::cout<<"  selection - states the number of objs in the selection"<<std::endl;
  std::cout<<"  selection show - shows the object names in the selection"<<std::endl;
  std::cout<<"  selection add [name/type] [?typename (if type)] - adds the object(s) with those name(s) (csv) or that type to the selection";
  std::cout<<"  selection clear - clears the selection"<<std::endl;
  std::cout<<"export selection/all [file path] - exports the current selection or all objects to a formatted csv file"<<std::endl;
  std::cout<<"read [file path] - attempts to read the contents of the provided file into the catalouge"<<std::endl;
  std::cout<<"add [type] [input string] - attempts to add the type of object/observation the input string must be formmated like the files"<<std::endl;
  std::cout<<"remove [name] - removes the corresponding object from the catalouge"<<std::endl;
  std::cout<<"projection all/selection [file name] - creates a Mollweide projection of the celesital sphere and projects the selected data points on it, exports this to a bmp file."<<std::endl;
  std::cout<<"report - generates a report on the current catalouge, outputs it to the console"<<std::endl;
}

void Catalouge::open_cli_interface()
{
  bool running = true;
  std::string user_input;
  std::vector<std::string> tokenized_input;
  std::vector<std::string> selection;
  std::cout<<"Astronomical Object Catalouge CLI opened"<<std::endl;
  std::cout<<"Type h for help or exit to exit the interface."<<std::endl;
  //Continues aren't strictly neccesary in this but for clartiy included to show the end of logic chains
  while(running)
  {
    user_input.clear();
    tokenized_input.clear();
    std::getline(std::cin, user_input);
    
    tokenized_input = tokenizer(user_input,' ');
    if (tokenized_input.size() == 0)
    {
      std::cout<<"Command not recognised, type h for help or exit to exit"<<std::endl;
      continue;
    }
    if (tokenized_input[0] == "exit") 
    {
      std::cout<<"Exiting interface"<<std::endl;
      running = false; //not strictly neccesary but for clarity
      break;
    }
    else if(tokenized_input[0] == "h" || tokenized_input[0] == "help")
    {
      print_help_information();
      continue;
    }
    else if(tokenized_input[0] == "validobjtypes")
    {
      print_vector(valid_obj_types);
      continue;
    }
    else if(tokenized_input[0] == "validobstypes")
    {
      print_vector(valid_observation_types);
      continue;
    }
    else if(tokenized_input[0] == "list")
    {
      if(tokenized_input.size() == 1)
      {
        print_catalouge_names();
        continue;
      }
      else if(tokenized_input.size() == 2)
      {
        print_catalouge_names(tokenized_input[1]);
        continue;
      }
      else
      {
        std::cout<<"Could not parse list command"<<std::endl;
        continue;
      }
    }
    else if(tokenized_input[0] == "print")
    {
      if(tokenized_input.size() == 2)
      {
        std::vector<std::string> tokenized_names = tokenizer(tokenized_input[1],',');
        if(tokenized_names[0] == "all")
        {
          for(auto const& x : catalouge_map) //print all by iterating map
          {
            x.second->print_all_information();
          }
          continue;
        }
        else if(tokenized_names[0] == "selection") //print selection by iterating selection keyss
        {
          for(int i = 0; i<selection.size(); i++)
          {
            catalouge_map[selection[i]]->print_all_information();
          }
          continue;
        }
        else
        {
          for(size_t i = 0; i<tokenized_names.size(); i++)
          {
            if(catalouge_map[tokenized_names[i]])
            {
              catalouge_map[tokenized_names[i]]->print_all_information();
            }
            else
            {
              std::cout<<"Failed to find information for: "<<tokenized_names[i]<<std::endl;
            }
          }
          continue;
        }
      }
      else
      {
          std::cout<<"Invalid arguments, could not parse the print command given"<<std::endl;
          continue;
      }
    }
    else if(tokenized_input[0] == "export")
    {
      if(tokenized_input.size() == 3) 
      {
        if(tokenized_input[1] == "selection")
        {
          export_file(tokenized_input[2],selection);
          continue;
        }
        else if(tokenized_input[1] == "all")
        {
          export_file(tokenized_input[2],get_catalouge_keys()); 
          continue;
        }
        else
        {
          std::cout<<"Could not parse the export command"<<std::endl;
          continue;
        }
      }
      else
      {
        std::cout<<"Could not parse the export command"<<std::endl;
        continue;
      }
    }
    else if(tokenized_input[0] == "selection")
    {
      if(tokenized_input.size() == 1)
      {
        std::cout<<"Currently there are "<<selection.size()<<" objects in the selection"<<std::endl;
        continue;
      }
      else if(tokenized_input.size() == 2)
      {
          if(tokenized_input[1] ==  "clear")
          {
              selection.clear();
              std::cout<<"Cleared selection"<<std::endl;
              continue;
          }
          else if(tokenized_input[1] ==  "show")
          {
              for(size_t i = 0;i<selection.size();i++)
              {
                  std::cout<<selection[i]<<" ";
              }
              std::cout<<std::endl;
              continue;
          }
          else
          {
              std::cout<<"Could not parse the selection command"<<std::endl;
              continue;
          }
      }
      else if(tokenized_input.size() == 3)
      {
          std::vector<std::string> tokenized_names = tokenizer(tokenized_input[2],',');
          if(tokenized_input[1] == "add")
          {
              if(tokenized_names[0] == "all")
              {
                  for(auto const& x : catalouge_map)
                  {
                      if(is_within_set(x.first,selection))
                      {
                      }
                      else
                      {
                          selection.push_back(x.first);
                      }
                  }
                  std::cout<<"Added all to the selection"<<std::endl;
                  continue;
              }
              else
              {
                  for(size_t i = 0; i<tokenized_names.size();i++)
                  {
                      if(catalouge_map.find(tokenized_names[i]) != catalouge_map.end()  && (is_within_set(tokenized_names[i],selection) == false))
                      {
                          selection.push_back(tokenized_names[i]);
                      }
                  }
                  std::cout<<"Added objects to selection"<<std::endl;
                  continue;
              }
          }
          else
          {
              std::cout<<"Could not parse the selection command"<<std::endl;
              continue;
          }
      }
      else if (tokenized_input.size() == 4)
      {
        if(tokenized_input[1] == "add" && tokenized_input[2] == "type")
        {
          std::vector<std::string> type_names = tokenizer(tokenized_input[3],',');
          std::cout<<type_names[0]<<std::endl;
          for(auto const& x : catalouge_map)
          {
            if((is_within_set(x.first,selection) == false) && (is_within_set(x.second->get_obj_type(),type_names)))
            {
              selection.push_back(x.first);
            }
          }
          std::cout<<"Added types to selection"<<std::endl;
          continue;
        }
        else
        {
          std::cout<<"Failed to parse selection command"<<std::endl;
          continue;
        }
      }
      else
      {
        std::cout<<"Could not parse the selection command"<<std::endl;
        continue;
      }
    }
    else if(tokenized_input[0] == "add")
    {
      if(tokenized_input.size() == 3)
      {
        if(tokenized_input[1] == "object")
        {
          try
          {
            add_object_string(tokenized_input[2]);
            std::cout<<"Added object"<<std::endl;
            continue;
          }
          catch(const std::exception& e)
          {
            std::cerr<<"Failed to execute input. Reason:"<<std::endl;
            std::cerr << e.what() << '\n';
            continue;
          }
        }
        else if(tokenized_input[1] == "observation")
        {
          try
          {
            add_observation_string(tokenized_input[2]);
            std::cout<<"Added observation"<<std::endl;
            continue;
          }
          catch(const std::exception& e)
          {
            std::cerr<<"Failed to execute. Reason:"<<std::endl;
            std::cerr << e.what() << '\n';
            continue;
          }
        }
        else
        {
            std::cout<<"Failed to parse add command"<<std::endl;
            continue;
        }
      }
      else
      {
        std::cout<<"Failed to parse add command"<<std::endl;
        continue;
      }
    }
    else if (tokenized_input [0] == "remove")
    {
      if(tokenized_input.size() ==  2)
      {
        if(tokenized_input[1] == "selection")
        {
          for(int i = 0; i<selection.size();i++)
          {
            remove_object((selection[i]));
          }
          std::cout<<"Removed selection"<<std::endl;
        }
        else
        {
          try
          {
            remove_object(tokenized_input[1]);
            std::cout<<"Removed object"<<std::endl;
            continue;
          }
          catch(const std::exception& e)
          {
            std::cerr << e.what() << '\n';
          }
        }
      }
      else if(tokenized_input.size() == 1)
      {
        std::cout<<"No object name provided"<<std::endl;
        continue;
      }
      else
      {
        std::cout<<"Failed to parse remove command"<<std::endl;
        continue;
      }
    }
    else if(tokenized_input [0] == "read")
    {
      if(tokenized_input.size() == 2)
      {
        read_file(tokenized_input[1]);
        continue;
      }
      else if(tokenized_input.size() == 1)
      {
        std::cout<<"No file name provided"<<std::endl;
        continue;
      }
      else
      {
        std::cout<<"Failed to parse read command"<<std::endl;
        continue;
      }
    }
    else if(tokenized_input[0] == "report")
    {
      print_report();
      continue;
    }
    else if(tokenized_input[0] == "projection")
    {
      if(tokenized_input.size() == 3)
      {
        if(tokenized_input[1] == "all")
        {
          try
          {
            make_projection_selection(get_catalouge_keys(),tokenized_input[2]);
            std::cout<<"Projection made"<<std::endl;
          }
          catch(const std::exception& e)
          {
            std::cerr<<"Failed to make projection"<<std::endl;
            std::cerr << e.what() << '\n';
          }
        }
        else if(tokenized_input[1] == "selection")
        {
          try
          {
            make_projection_selection(selection,tokenized_input[2]);
            std::cout<<"Projection made"<<std::endl;
          }
          catch(const std::exception& e)
          {
            std::cerr<<"Failed to make projction"<<std::endl;
            std::cerr << e.what() << '\n';
          }
        }
        else
        {
          std::cout<<"Failed to parse projection command"<<std::endl;
        }
      }
      else
      {
        std::cout<<"Failed to parse projection command"<<std::endl;
      }
    }
    else
    {
      std::cout<<"Command not recognised, type h for help or exit to exit"<<std::endl;
      continue;
    }
  }
}