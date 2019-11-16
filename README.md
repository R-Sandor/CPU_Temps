# CPU Temps
This program will takes the readings from N (in our case 4) cores 
in a CPU. Each reading was taken in 30 second internvals.

The program takes the reading from the input files of each core and 
finds the line of best fit and outputs the point of best fit for 
each point with least squares.

The program all provides the output of interpolation at each point.

Provided core readings courtesy of Professor Thomas J. Kennedy at ODU. 


# Requirements
> gcc
> gnu make


# Project Layout
## build
> compiled src code excluding the program executable

## Include
> .h files

## res
> Resource files, CPU temparature readings.

## src
> Source code


# Setup/Compilation & Execution Instructions  
- Untar package.
- modify the makefile and supply the path to the apporiate BOOST_ROOT (currently set at the convention of /usr/local/boost_#LibNumber#)	I am using boost_1_71_0.
or specify your boost directory when make is ran by issuing the following command:

 make BOOST_ROOT='/your/boost/dir'

- make

### To Run
> ./CpuTemps res/sensors-2018.12.26-no-labels.txt
The program only takes one parameter, the file path
to matrix one wishes to solve.





# Author 
Raphael J. Sandor
