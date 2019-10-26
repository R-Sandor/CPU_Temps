#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <vector>
/*
 *	This function returns the number of word/numbers inside of a string
 */
int itemCount(std::string str, std::string delim);

/*
 *	very similar to the other function above but returns a vector from a given string.
 */
std::vector<double> stringToVector(std::string str, std::string delim);

/*
 * Prints a given matrix out to console.
 */
void printMatrix(std::vector<std::vector<double> > matrix);

#endif
