/**
 * @Author:	Raphael J. Sandor
 * @Date:	10/26/2019
 * @Version: 1.0
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
 *	@param lhs left-hand side matrix
 *	@param rhs right-hand side matrix 
 *
 *	Assumption: Matrix need to be correct demensions have a valid result. 
 *	2X3 Matrix needs to be multiplied against a 3X2 matrix.
 *
 */
void  multiplyer(vector<vector<double>> lhs, vector<vector<double>> rhs, vector<vector<double> >& result)
{
	int lhsRows = lhs.size();
	int lhsCols = lhs[0].size();
	int rhsRows = rhs.size();
	int rhsCols = rhs[0].size();
    
	cout << "lhsRow: " <<  lhsRows << endl << "lhsCols: " << lhsCols << endl << "rhsRows: " << rhsRows << endl << "rhsCols: "  << rhsCols << endl << endl;
	for (int i = 0; i < lhsRows; i++)
	{	
		vector<double> row (rhsCols);
		result.push_back(row);
		for (int j = 0; j < rhsCols; j++)
		{
			for (int k = 0; k < lhsCols; k++)
			{
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}

}	

/**
 *	@param matrix		The original matrix
 *	@param lrgstCol		The row (i.e. vector) with the largest column
 *	@loopIter			The iteration of the calling loop.
 *	Swaps vector indices.
 */
void swapRow(vector<vector<double> > &matrix, int loopIter, int lrgstCol)
{

	swap(matrix[loopIter], matrix[lrgstCol]);
}


vector<vector<double>> createXMatrix(vector<double> &timeVector)
{
	vector<vector<double> > xMatrix;
	vector<double> onesVect;

	for (int i = 0; i < timeVector.size(); i++)
	{
		onesVect.push_back(1);
	}
	xMatrix.push_back(onesVect);
	xMatrix.push_back(timeVector);
	return xMatrix; 
}

vector<vector<double> > createTMatrix(vector<vector<double> > &inMatrix)
{
	vector<vector <double> >tMatrix (inMatrix[0].size());
	int inMatCols = inMatrix[0].size();
	for (int i = 0; i < inMatrix.size(); i++)
			for (int j = 0; j < inMatCols ; j++)
			{
				if (i == 0)
				{
					vector<double> row (inMatrix.size()); 
					row[0] = inMatrix[0][j];
					tMatrix[j] = row;
				}	
					tMatrix[j][i] = inMatrix[i][j];
				
			}
	return tMatrix;
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

/**
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

/**
 * @param matrix The matrix that will be backed solved.
 *
 * At this point the matrix has been established into the well known
 * diagnol matrix.
 * 1 # # | # \n
 * 0 1 # | # \n
 * 0 0 1 | # \n
 * 
 * and the remaining #'s in the A matrix need to be 
 * replaced with 0 and the c vector need to reflect the appropriate
 * values. 
 *
 */

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
 *	@param argc Argument count
 *	@param argv Takes file path
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
				core.push_back(inputLine[indexOfCore-1]);
			// push each core into its own vector	
			data.push_back(core);
		}

		int count = 1; 
		while (getline(dataFile, line) )
		{
			// Now we want to take the output of each row and add it to its respective vector
			inputLine = stringToVector(line, delim);
			for (int indexOfCore = 0; indexOfCore < cores ; indexOfCore++)
			{
				if (indexOfCore == 0)
				{
					data[indexOfCore].push_back(count * 30);
					continue;
				}	
				else
					data[indexOfCore].push_back(inputLine[indexOfCore-1]);
				count++;						
			}
		}
		
/*		
		// Print my input data file..
		for (int i = 0; i < data[1].size(); i++)
		{
			for (int j = 0; j < cores; j++)
			{
				cout << data[j][i] << " ";
			}
			cout << endl;
		}
*/	
		vector<vector<double> > xMatrix;
		vector<vector<double> > xTMatrix;
		xMatrix = createXMatrix(data[0]);
/*
		for (int i = 0; i < xMatrix[0].size(); i++)
		{
			for (int j = 0; j < xMatrix.size(); j++)
			{
				cout << xMatrix[j][i] << " ";
			}
			cout << endl;
		}
*/





		xTMatrix = createTMatrix(xMatrix);
		
		// Print my input data file..
		for (int i = 0; i < xTMatrix[0].size(); i++)
		{
			for (int j = 0; j < xTMatrix.size(); j++)
			{
				cout << xTMatrix[j][i] << " ";
			}
			cout << endl << endl;
		}
		vector<vector<double> > xTxMatrix;
		
		multiplyer(xMatrix, xTMatrix, xTxMatrix);
		cout << xTxMatrix.size() << endl;	

		cout << xTxMatrix[0].size() << endl;



    vector<vector<double> > matrixA { {1,1,1},
                                      {0,30,60}
                                    };
    vector<vector<double> > matrixB {
                                      {1,2,3, 4},
                                      {4,5,6, 7},
                                      {7,8,9, 10},
									  {11,12,13,14}
									  
                                    };
	vector<vector<double> >matrix2;

	vector<vector<double> >matrix3;
	matrix2 = createTMatrix(matrixA);
	printMatrix(matrix2);
	printMatrix(matrixA);
	multiplyer(matrixA, matrix2, matrix3);

//	printMatrix(xTxMatrix);
	printMatrix(matrix3);
}
