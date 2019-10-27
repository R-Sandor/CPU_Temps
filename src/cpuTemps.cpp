/*
 * Author:	Raphael J. Sandor
 * Date:	10/26/2019
 * Version: 1.0
 * 
 * Description: 
 *		This program reads in a file of CPU core tempatures and find the line of best fit
 *		using either least squares or interpolation.
 *		The program then exports the approximation for a point to a txt file. 
 */

#include <iostream>
#include <fstream> //File reader(ifstream)
#include <vector>

#include "matrixSolver.h"
#include "helper.h"

using namespace std;


/**
 *	@param lhs left-hand side 
 *	@param rhs right-hand side
 *
 */
vector<vector<double>>  multiplyer(vector<vector<double>> lhs, vector<vector<double>> rhs)
{
	int lhsRows = lhs.size();
	int lhsCols = lhs[0].size();
	vector<vector<double> > result(lhs.size());
    			
	for (int i = 0; i < lhsRows; i++)
	{	
		result[i] = vector<double>(rhs.size());
		for (int j = 0; j < lhsCols; j++)
			for (int k = 0; k < lhsCols; k++)
				result[i][j] += lhs[i][k] * rhs[k][j];
	}
	return result;

}	

/*
 *	Swap vector indices.
 */
void swapRow(vector<vector<double> > &matrix, int loopIter, int lrgstCol)
{

	swap(matrix[loopIter], matrix[lrgstCol]);
}


vector<vector<double>> createXMatrix(vector<double> &timeVector)
{
	vector<vector <double> > xMatrix;
	vector<double> onesVect;

	for (int i = 0; i < timeVector.size(); i++)
	{
		onesVect.push_back(1);
	}
	xMatrix.push_back(onesVect);
	xMatrix.push_back(timeVector);
	return xMatrix; 
}

/*
 *	Finds the row which the largest column belongs.
 */
int findLargestCol(vector<vector<double> > &matrix, int col)
{
	int largest = 0;
	double largestVal = 0.0;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (matrix[i][col] > largestVal)
		{
			largest = i;
			largestVal = matrix[i][col];
		}

	}
	return largest;
}

/*
 *	Takes a matrix, and for each row (i.e. iteration of the calling loop).
 *	Scalar used to scale the matrix.
 */
void scale(vector<vector<double> > &matrix, int loopIter, double scalar)
{
	for (int cIndex = 0; cIndex < matrix[0].size(); cIndex++)
	{
		// the loopIter is the row that is being manipulated.
		matrix[loopIter][cIndex] = matrix[loopIter][cIndex] / scalar;
	}
}

void eliminate(vector<vector<double> > &matrix, int rowIt)
{
	// Start column.
	int sCol = rowIt;
	for (int i = rowIt + 1; i < matrix.size(); i++)
	{
		double scalar = matrix[i][rowIt];

		for (int j = sCol; j < matrix[0].size(); j++)
		{
			matrix[i][j] = matrix[i][j] - scalar * matrix[rowIt][j];
		}
		matrix[i][sCol] = 0;
	}

}

void backSolve(vector<vector<double> >&matrix)
{
	int augCol	= matrix[0].size()-1;
	int lastRow = matrix.size() -1;
	for (int i = lastRow; i >=  1; i--)
	{
		for( int j = i-1; j >= 0; j--)
		{
			double scalar = matrix[j][i];
			matrix[j][i] -= scalar * matrix[i][i];
			matrix[j][augCol] -= scalar *matrix[i][augCol];
		}	
	}
}

/**
 *	@param argv takes file path
 *
 */
int main(int argc, char **argv )
{
	if (argv[1] == NULL)
	{
		cout << "Error: Please provide path to the data file. Refer to the README.md" << endl;
		return 1;
	}
	if (argc == 1)
	{	
		cout << "Please run program again with file path to data file" << endl;
		return 1;
	}

	//	readFile
	ifstream dataFile;
	// path to file
	string path = argv[1];
	
	string line;
	string delim = " "; 

	// Number of cores to be reading data from.
	int cores;
	vector< vector<double> > data;	


	// Check if the path is correct.	
	dataFile.open(path);
	if (!dataFile)
	{
		cout << "Error: File not found, check file path"<< endl;
		return 1;
	}
	if (dataFile.is_open())
		getline(dataFile, line);
		vector<double> inputLine = stringToVector(line, delim);
		// If there are four cores, we want to register it as 5
		// 1 for the time of recording.
		cores = inputLine.size() + 1;

		// element 0 for the time vector
		// e.g. 30, 60, 90, 120	
		for (int indexOfCore = 0; indexOfCore < cores; indexOfCore++)
		{
			vector<double> core;
			if (indexOfCore == 0)
				core.push_back(0);
			else
				core.push_back(inputLine[indexOfCore]);
			// push each core into its own vector	
			data.push_back(core);
		}

		int count = 0; 
		while (getline(dataFile, line) )
		{
			// Now we want to take the output of each row and add it to its respective vector
			inputLine = stringToVector(line, delim);
			for (int indexOfCore = 0; indexOfCore < cores ; indexOfCore++)
			{
				if (indexOfCore == 0)
				{
					data[indexOfCore].push_back(count * 30);
					count++;						
					continue;
				}	
				else
					data[indexOfCore].push_back(inputLine[indexOfCore-1]);
			}
		}

		// Print my input data file..
		for (int i = 0; i < data[1].size(); i++)
		{
			for (int j = 0; j < cores; j++)
			{
				cout << data[j][i] << " ";
			}
			cout << endl;
		}
		
		vector<vector<double> > xMatrix;
		xMatrix = createXMatrix(data[0]);
		for (int i = 0; i < xMatrix[0].size(); i++)
		{
			for (int j = 0; j < cores; j++)
			{
				cout << data[j][i] << " ";
			}
			cout << endl;
		}
		
}
