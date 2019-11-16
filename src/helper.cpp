/*
 * Useful utilities for the Matrix solver. 
 *
 */

#include <iostream>
#include <vector> //used for print matrix 
#include <iomanip> //setprecision
#include "helper.h"

/**
 * Counts the number of items in a string
 * @param str	a given string
 * @param delim the given delimiter
 */
using namespace std;
int itemCount(string str, string delim)
{
	int count = 0;
	auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos)
    {
        start = end + delim.length();
		end = str.find(delim, start);
		count++;
    }
	if (count != 0)
		count++;

	return count;

}

/**
 * Converts a string of numbers to a vector
 * e.g. string str ="10 11 12", would become
 * a vector of size 3, holding 10, 11, and 12.
 *
 * @param str		a given string.
 * @param delim		delimiter
 */
vector<double> stringToVector(string str, string delim)
{
	auto start = 0U;
    auto end = str.find(delim);
	vector<double> retVect;
	int count = 0;
    while (end != std::string::npos)
    {
		count++;
		string parsed = str.substr(start, end - start);
		double valToAdd = stod(parsed);
		retVect.push_back(valToAdd);
        start = end + delim.length();
		end = str.find(delim, start);
    }
	if (count >0)
	{
		string parsed = str.substr(start, end - start);
		double valToAdd = stod(parsed);
		retVect.push_back(valToAdd);
	}
	return retVect;

}

/**
 *	outputs a matrix
 *	@param matrix matrix to be printed.
 */
void printMatrix(vector<vector<double> > matrix)
{
	for (int i = 0; i < 15 + matrix.size() * 8 + 2; i++)

		cout << "-";
	cout << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (j == 0)
				cout << "| ";
			if (j == matrix[i].size()-1)
			{
				cout << "| " << setw(10) << matrix[i][j] << "|";
				continue;
			}
			cout << setw(8) <<  setprecision(8) << matrix[i][j] << " "; 
		}
		cout << endl;
	}
	for (int i = 0; i < matrix.size()*8 +15 + 2; i++)
		cout << "-";
	cout << endl;
}

/**
 *	tells user if double is an int
 *	@x a given double
 */
bool double_is_int(double x) {
   double absolute = abs( x );
   return absolute == floor(x);
}
