// Name: Awwab Butt ID: 11091269 Date: 4/5/2025
// Description:
/*
Implementation file for projection h
*/

#include "projection.h"

#include <memory>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <string>
#include <exception>

double convert_deg_to_radian(double theta)
{
  return (theta * pi / 180);
}

// Newton raphson implementation with function pointers (in the std::function wrapper) for arbritrary functions to be as generalised as possible

static double solve_theta(double lat)
{
  /*bear in the mind this lat is in radians
  does a newton raphson solve for the 2theata + 2sintheata = pi sin phi auxiallary angle
  static becasue its a common name and only want within this file scope*/
  double delta = 1e-9;
  int iterations = 100;
  double theta = lat; 
  //lamba functions of the theta and theta prime sent, need to explicitly cast the return as double as thats what the function pointers require 
  theta = newton_raphson<double>([lat](double theta) -> double { return (2*theta+std::sin(2*theta)-pi * std::sin(lat)); },[](double theta) -> double {return(2+2*std::cos(2 * theta));},theta, delta, iterations, 1e-9);
  return theta;
}

std::pair<double, double> forward_mollweide(double lat, double longn, double radius, double meridian)
{
  // does the forward Mollweide Projection, forward specified since backwards is used alot and is clearn
  // returns a pair of x,y coordinates corresponding to the position on the sphere
  double theta = solve_theta(lat);
  double x = radius * ((2 * std::sqrt(2)) / (pi)) * (longn - meridian) * std::cos(theta);
  double y = radius * (std::sqrt(2)) * std::sin(theta);
  return {x, y};
}

std::pair<double, double> inverse_mollweide(double x, double y, double radius, double meridian)
{
  // Performs the inverse mollweide
  double theta = std::asin(y / (radius * std::sqrt(2.0)));
  double lambda;
  double phi;
  if (std::cos(theta) == 0 || std::abs(std::cos(theta)) <= 1e-9) // handling undefined cos90 at +- 90
  {
    lambda = 0;
    if (y > 0)
    {
      phi = pi / 2; //=90
    }
    else
    {
      phi = -pi / 2;
    }
  }
  else
  {

    // Using the nice inverse equations for the projection
    lambda = meridian + pi * x / (2.0 * radius * std::sqrt(2.0) * std::cos(theta));
    phi = std::asin((2 * theta + std::sin(2 * theta)) / pi);
  }
  return {lambda, phi};
}

void draw_bmp(const std::string &file_name, std::vector<std::vector<Pixel>> pixels)
{
  // writes all the header paramters needed for a BMP file.
  // Goes through all of the values, read to be set then converts to binary and appends to the file
  // Most of this is just boilerplate, the pixel data is appended at the end
  if (is_empty_or_whitespace(file_name))
  {
    throw std::runtime_error("file_name_is_empty");
  }
  if (file_name.length() < 5)
  {
    throw std::runtime_error("file_name_must_be_atleast_one_character");
  }
  std::string extension = file_name.substr(file_name.length() - 4, 4);
  if (extension != ".bmp")
  {
    throw std::runtime_error("file_name_must_end_with_.bmp");
  }
  std::ofstream file(file_name, std::ios::binary); // opens in binary mode
  if (!file.is_open())
  {
    throw std::runtime_error("file_failed_to_open");
  }
  file << ('B');
  file << ('M');
  unsigned int file_size = 14 + 40 + img_width * img_height * 3; // Each pixel 3 bytes 8bit rgb and the headers and 14 and 40 bytes each
  file.write((char *)(&file_size), 4);                           // adds file_size to the header, 4 bytes beacaue unsigned int is 4 bytes
  file.put(0);
  file.put(0);
  file.put(0);
  file.put(0);                             // 4 Future? bytes for bitmap
  unsigned int header_offset = 14 + 40;    // This is the file offset from the two headers, data starts after
  file.write((char *)(&header_offset), 4); // same as file_size
  unsigned int header_size = 40;           // dib header size
  file.write((char *)(&header_size), 4);   // writing header size to file in binary
  file.write((char *)(&img_width), 4);     // adding width and height to header
  file.write((char *)(&img_height), 4);
  unsigned short colour_plane = 1;
  file.write((char *)(&colour_plane), 2); // color plane typically 1 or always 1
  unsigned short bit_depth = 24;          // bits per pixel 8*3 bytes is 24 bits
  file.write((char *)(&bit_depth), 2);
  unsigned int compression = 0; // uncompressed file so 0;
  file.write((char *)(&compression), 4);
  unsigned int img_size = 0; // 0 for this type of image
  file.write((char *)(&img_size), 4);
  unsigned int ppm_x = 0; // pixel per meter resolution is 0
  file.write((char *)(&ppm_x), 4);
  unsigned int ppm_y = 0;
  file.write((char *)(&ppm_y), 4);
  unsigned int pallette = 0; // allows or all colours
  file.write((char *)(&pallette), 4);
  unsigned int imp_colour = 0; // all important
  file.write((char *)(&imp_colour), 4);
  int padding = (4 - (img_width * 3) % 4) % 4; // padding is 4 bytes per pixel per row
  for (int y = 0; y < img_height; y++)         // iterates through pixel 2D vector adding the rgb values to the file stream
  {
    for (int x = 0; x < img_width; x++)
    {
      // std::cout<<x<<","<<y<<std::endl;
      // Inserting pixel data, its BGR format, 1 byte allocated per channel conver to binary then add
      file.put(pixels[x][y].blue);
      file.put(pixels[x][y].green);
      file.put(pixels[x][y].red);
    }
    for (int i = 0; i < padding; i++)
    {
      file.put(0); // adds the extra padding needed per row
    }
  }
  file.close();
}
std::vector<std::vector<Pixel>> make_base_ellipse() // makes the standard ellipse from which the projections are based
{
  const Pixel blank{255, 255, 255};
  const Pixel black{0, 0, 0};
  const Pixel grid_colour{0, 0, 255}; //orange

  std::vector<std::vector<Pixel>> pixels(img_width, std::vector<Pixel>(img_height, blank)); // make a blank pixel grid

  // r=1 assumption results in the following bounds
  double proj_x_bound = 2.0 * std::sqrt(2.0);
  double proj_y_bound = std::sqrt(2); // symmetric so can use this
  double lattiude_step = 15.0;
  double longnitude_step = 15.0; // the size of the grid in degrees
  double grid_tolerance = convert_deg_to_radian(0.4);

  for (int y = 0; y < img_height; y++) // iterates through every pixel
  {
    for (int x = 0; x < img_width; x++)
    {
      // converting from image pixel coords to the projection centred coords
      double x_proj = (double)x / (img_width - 1) * (proj_x_bound * 2) - proj_x_bound;
      double y_proj = ((double)y / (img_height - 1)) * (proj_y_bound * 2) - proj_y_bound;

      // calculating if point is within the ellipse
      double ellipse_distance = (std::pow(x_proj, 2) / (std::pow(proj_x_bound, 2))) + ((std::pow(y_proj, 2)) / (proj_y_bound, 2));

      if (ellipse_distance <= 1) // If it is, turns it black
      {
        pixels[x][y] = Pixel{0, 0, 0};
      }

      std::pair<double, double> inverse_mol = inverse_mollweide(x_proj, y_proj); // performss an inversse on the xand yproj
      double lambda = inverse_mol.first;
      double phi = inverse_mol.second;
      // both for loops iterate through lat and long createing the gridlines
      // now uses the tolerance approach, previosuly positions on the grid were calculated by forward mollweide but that resulted in gaps
      // now an inverse mollweide per pixel is used then compared to a grid tolerance much easier. Future update would make use of line point to point rendering but didnt have time for the implementation
      for (double lattiude = -90; lattiude <= 90; lattiude += lattiude_step)
      {
        double lat_r = convert_deg_to_radian(lattiude);
        if (std::abs(phi - lat_r) < grid_tolerance)
        {
          pixels[x][y] = grid_colour;
          break;
        }
      }
      for (double longnitude = -180.0; longnitude <= 180.0; longnitude += longnitude_step)
      {
        double lon_grid_rad = convert_deg_to_radian(longnitude);
        if (std::abs(lambda - lon_grid_rad) < grid_tolerance)
        {
          pixels[x][y] = grid_colour;
          break;
        }
      }
      // Performs a final mask to remove all the extra lat/long lines making a blank(white) background
      if (ellipse_distance > 1)
      {
        pixels[x][y] = blank;
      }
    }
  }
  return pixels;
}

void add_object_to_projection(const BaseAstronomicalObject &object, std::vector<std::vector<Pixel>> &pixels)
{
  ObservationErrorEllipse<double> coordinates = object.get_coords();
  std::string obj_type = object.get_obj_type();
  Pixel colour = Pixel{255, 255, 255}; // the default colour is white
  if (obj_type == "star")
  {
    colour = Pixel{0, 255, 255}; // yellow
  }
  else if (obj_type == "planet")
  {
    colour = Pixel{0, 255, 0}; // green
  }
  else if (obj_type == "galaxy")
  {
    colour = Pixel{230, 43, 140}; // purple
  }
  double right_ascenion = coordinates.get_obs_ra();
  double declination = coordinates.get_obs_dec();
  double lattiude = convert_deg_to_radian(declination);            // converting ra to lattiude type coords
  double longnitude = convert_deg_to_radian(right_ascenion - 180); // 0-360 to -180,180
  std::pair<double, double> projected_coords = forward_mollweide(lattiude, longnitude);
  double proj_x_bound = 2.0 * std::sqrt(2.0);
  double proj_y_bound = std::sqrt(2.0);                                                                     // symmetric so can use this
  int coord_x = std::floor(((((projected_coords.first + proj_x_bound)) / (proj_x_bound * 2))) * img_width); // convertss from projection to pixel coords
  int coord_y = std::floor((((proj_y_bound + projected_coords.second) / (proj_y_bound * 2)) * img_height));

  int scaled_size = img_width / 200;    // Provides scalling relative to the image size
  for (int i = 0; i < scaled_size; i++) // creates a square for easy visualisation of the object position
  {
    for (int j = 0; j < scaled_size; j++)
    {
      if (coord_x + i >= 0 && coord_x + i < img_width, coord_y + j >= 0 && coord_y + j < img_height - 1)
      {
        pixels[coord_x + i][coord_y + j] = colour;
      }
    }
  }
}
