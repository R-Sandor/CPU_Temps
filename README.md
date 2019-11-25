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

> GNUmake


> Boost 1.71.0 (https://www.boost.org/users/download/)

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
- modify the makefiles under the project directory and the test directory and 
supply the path to the apporiate BOOST_ROOT 
(currently set at the convention of /usr/local/boost_#LibNumber#)
I am using boost_1_71_0. 

You may specify your boost directory when GNUmake 
is ran by issuing the following command:

- make BOOST_ROOT='/your/boost/dir'
- make test BOOST_ROOT='/your/boost/dir'

## Build Directives:

### make test
- Builds and Runs test cases

### make clean
- clean all of the binaries including test's binaries

### make run_test
- Runs the compiled test cases.


## To Run:
> ./CPUTemps res/sensors-2018.12.26-no-labels.txt


The program only takes one parameter, the file path
to matrix one wishes to solve.


### Acknowledgements
I would like to give special thanks to my colleague at Alion Science and Technology,
Jason Lafoutain for recommending the use of Catch2 unit testing for C++ when we were 
disscussing unit testing options for C++.


# Author 
Raphael J. Sandor
