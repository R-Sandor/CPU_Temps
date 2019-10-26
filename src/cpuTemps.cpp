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


int main(int argc, char **argv )
{
	if (argv[1] == NULL)
	{
		cout << "Error: Please provide path to the matrix file. Refer to the README.md" << endl;
		return 1;
	}
	if (argc == 1)
	{	
		cout << "Please run program again with in file path to matrix input file" << endl;
		return 1;
	}
	vector<vector<double> > matrixA { {1,2,3},
									  {4,5,6}
									};
	vector<vector<double> > matrixB {
									  {1,2,3},
									  {4,5,6},
									  {7,8,9}
									};

	//The read in matrix
	vector<vector<double>> matrix;
	string line;
	// used for vector parser helper functions
	string delim = " ";
	//	readFile
	ifstream matrixFile;
	// path to file
	string path = argv[1];

	// Check if the path is correct.	
	matrixFile.open(path);
	if (!matrixFile)
	{
		cout << "Error: File not found, check file path"<< endl;
		return 1;
	}
	if (matrixFile.is_open())
			while (getline(matrixFile, line) )
			{
				vector<double> inputLine = stringToVector(line, delim);
				matrix.push_back(inputLine);
			}

	for (int i = 0; i < matrix.size()-1; i++)
	{
		int lrgstRow = findLargestCol(matrix, i);
		
		// swap the rows.
		swapRow(matrix, i, lrgstRow);
		
		// scale the row.
		scale(matrix, i, matrix[i][i]);
		matrix[i][i] = 1;
		eliminate(matrix, i);
	}
	double scalar = 0.0;
	// Lastrow needs to be solved.
	scalar = 1/matrix[matrix.size()-1][matrix[0].size()-2];
	matrix[matrix.size()-1][matrix[0].size()-2] = 1;
	matrix[matrix.size()-1][matrix[0].size()-1] = matrix[matrix.size()-1][matrix[0].size()-1]*scalar;
	backSolve(matrix);
	printMatrix(matrix);

}
