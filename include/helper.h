#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <vector>
#include <math.h>

/**
 *	This function returns the number of word/numbers inside of a string
 *	@str a given input string
 *	@delim	a delimiter to separate items.
 */
int itemCount(std::string str, std::string delim);

/**
 *	very similar to the other function above but returns a vector from a given string.
 *	@str a given input string
 *	@delim a delimiter
 */
std::vector<double> stringToVector(std::string str, std::string delim);

/**
 * Prints a given matrix out to console.
 * @param matrix the matrix to printed
 */
void printMatrix(std::vector<std::vector<double> > matrix);

/**
 *	Determines if a given x is a int 
 *	@param x a double value to be checked.
 */
bool double_is_int(double x);

#endif
