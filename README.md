# Overview
This project is a modular astronomical data catalouge which can parse formatted csv files and read to them into accessible classes.<br>
It also supports command line data retreival and input aswell as outputting to a formatted .txt file <br>

#  Compiling 
This project is built in mind with c++17 comptability. It has been tested in windows 11 and a wsl instance of ubuntu using gcc. <br>

## Compilation Line
Using gcc you can compile the program from the workspace directory using:
```
g++ -std=c++17 main.cpp standard_tests/standard_input_validation.cpp classes/BaseAstronomicalObject.cpp classes/Star.cpp classes/Catalouge.cpp classes/Catalouge_io.cpp file_parsers/parsers.cpp classes/Galaxy.cpp classes/Planet.cpp projection/projection.cpp classes/observation/BaseObservation.cpp -o program
```
# Supported data

It currently supports the following objects:

- Stars
- Galaxiess
- Planets
- base (arbitrary observation)

# Usage
For an overview of the commands, compile and type h/help when the CLI opens for an overview of the commands

# CSV file formatting
Formatting information is inside the report aswell as the precise technical information and strucutre of the Class heirarchy inside a UML diagram [technical_report.pdf]
