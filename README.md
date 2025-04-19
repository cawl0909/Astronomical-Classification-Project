# Overview
This project is a modular astronomical data catalouge which can parse formatted csv files and read to them into accessible classes. <br>
It also supports command line data retreival and input aswell as outputting to a formatted .txt file <br>
This was built in mind with compatability with [SIMBAD](https://simbad.cds.unistra.fr/simbad/).

#  Compiling 
This project is built in mind with c++17 comptability and can be compiled in windows using gcc:

```
g++ -std
```
It can also be built from the make file provided
# Supported data

It currently supports the following objects:

- Stars
- Galaxiess
- Planets
- Systems
- Orbits 


# Overview of the class structure 

# CSV file formatting
The csv file formats are listed into vertical name, type pairs.<br>
They are read using the abstract class first then parsed using their specific parsers<br>
If the current line type is unsupported it will skip over it however this can be changed to exit the file read by changing the
skip_line flag in the file parser.<br>

The ? suffix corresponds to an optional data point<br>



## Fundemental abstract astronomical object
|type | Name |Right ascension|Declination|RA Err|Dec Err|Notes|
|-----|--------|----|----|----|----|----|
|string|string|double|double|double|double|string|

## Star class

## Galaxy class

## System Class

## Orbit class
