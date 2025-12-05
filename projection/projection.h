// Name: Awwab Butt ID: 11091269 Date: 28/4/2025
// Description:
/*
Mollweide Projection h file contains all the functions/structs needed for a Mollweide projection
image creator. The mollweide projection is used to reprsent the surface of a sphere as a 2d, famous cmb image.
It has two main sections, the Mollweide calculators and the bmp file generator which takes pixel data and creates a bmp
file with all the neccesary file headers
*/

#pragma once

#include <memory>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include "../classes/BaseAstronomicalObject.h"
#include "../classes/observation/CombinedObservations.h"

static const double pi = 3.14159265358979323846;
static int img_width = 2048; // needss to be 2:1 ratio for correct projection with no clipping
static int img_height = 1024;

struct Pixel //simple struct to contain rgb pixel data, set to unit8 since the bitdepth for colours used is 8bit*3 so 24bit for all 3
{ 
  uint8_t blue = 0;
  uint8_t green = 0;
  uint8_t red = 0;
};

double convert_deg_to_radian(double theta);
//Newton raphson template implementation
template<typename T> T newton_raphson(std::function<T(T)> f, std::function<T(T)> df, T guess, T tolerance, int max_iteration, T epsilon)
{
  T x = guess; // guess is the intial value
  for (size_t i = 0; i < max_iteration; i++)
  {
    T y = f(x);
    T y_prime = df(x);
    T x1 = x - (y / y_prime);
    if (abs(y_prime) < epsilon)
    {
      break;
    }
    if (std::abs(x1 - x) < tolerance)
    {
      return x1;
    }
    x = x1;
  }
  return x;
}

std::pair<double, double> forward_mollweide(double lat, double longn, double radius = 1.0, double meridian = 0); // forward mollweide projection returns pair of the x,y

std::pair<double, double> inverse_mollweide(double x, double y, double radius = 1, double meridian = 0); //inverse mollweide,

void draw_bmp(const std::string &file_name, std::vector<std::vector<Pixel>> pixels); // main function to create a bmp

std::vector<std::vector<Pixel>> make_base_ellipse(); // makes the base projection image with gridlines

void add_object_to_projection(const BaseAstronomicalObject &object, std::vector<std::vector<Pixel>> &pixels); // overlays object coord onto projection