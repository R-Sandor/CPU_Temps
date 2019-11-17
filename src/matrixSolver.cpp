#include <iostream>
#include <fstream> //File reader(ifstream)
#include <vector>

#include "matrixSolver.h"
#include "helper.h"
#include "interpolation.h"
using namespace std;
using boost::multiprecision::cpp_dec_float_50;


/**
 *	@param lhs left-hand side matrix
 *	@param rhs right-hand side matrix 
 *
 *	Assumption: Matrix need to be correct demensions have a valid result. 
 *	2X3 Matrix needs to be multiplied against a 3X2 matrix.
 *
 */
void  multiplyer(vector<vector<double>> &lhs, vector<vector<double>> &rhs, vector<vector<double> >&result)
{
	int lhsRows = lhs.size();
	int lhsCols = lhs[0].size();
	int rhsRows = rhs.size();
	int rhsCols = rhs[0].size();
   
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
 * @param lhs		matrix
 * @param rhs		vector
 * @param result	resulting matrix
 */
void  multiplyVectByMat(vector<vector<double>> &lhs, vector<double> &rhs, vector<vector<double> >& result)
{
	int lhsRows = lhs.size();
	int lhsCols = lhs[0].size();
	int rhsRows = rhs.size();
	int rhsCols = 1;
	
	for (int i = 0; i < lhsRows; i++)
	{	
		vector<double> row (rhsCols);
		result.push_back(row);
		for (int j = 0; j < rhsCols; j++)
		{
			for (int k = 0; k < lhsCols; k++)
			{
				
				result[i][j] += lhs[i][k] * rhs[k];
			}
		}
	}
}

/**
 *	Swaps vector indices.
 *	@param matrix		The original matrix
 *	@param lrgstCol		The row (i.e. vector) with the largest column
 *	@param loopIter		The iteration of the calling loop.
 */
void swapRow(vector<vector<double> > &matrix, int loopIter, int lrgstCol)
{

	swap(matrix[loopIter], matrix[lrgstCol]);
}

/**
 *	@param dataVect the vector that contains the temp values.
 */
vector<vector<double>> createXMatrix(vector<double> &dataVect)
{
	vector<vector<double> > xMatrix;
	vector<double> onesVect;
	for (int i = 0; i < dataVect.size(); i++)
	{
		xMatrix.push_back({1, dataVect[i]});
	}
	return xMatrix; 
}


/**
 *	@param inMatrix		inputMatrix used output the transpose  
 */
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
				else
					tMatrix[j][i] = inMatrix[i][j];
				
			}
	return tMatrix;
}


/**
 *	Finds the row which the largest column belongs.
 *	@param matrix	input matrix
 *	@param col		Which row has the largest col 
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
 *	
 *	@param matrix	input matrix
 *	@param loopIter	the count of time scaling has previously happened
 *	@param scalar	the value that scales the matrix
 *	
 */
void scale(vector<vector<double> > &matrix, int loopIter, double scalar)
{
	for (int cIndex = 0; cIndex < matrix[0].size(); cIndex++)
	{
		// the loopIter is the row that is being manipulated.
		matrix[loopIter][cIndex] = matrix[loopIter][cIndex] / scalar;
	}
}

/**
 *	The result is the matrix is solved.
 *	The swap and eliminate functions leave everything but the 
 *	last row that needs to solved and backSolv the whole matrix.
 *	@param xTx_xTyMatrix is the xTx_xTyMatrix
 */
void solveLastRow(vector<vector<double> > &xTx_xTyMatrix)
{

	double scalar = 1/xTx_xTyMatrix[xTx_xTyMatrix.size()-1][xTx_xTyMatrix[0].size()-2];
    xTx_xTyMatrix[xTx_xTyMatrix.size()-1][xTx_xTyMatrix[0].size()-2] = 1;
    xTx_xTyMatrix[xTx_xTyMatrix.size()-1][xTx_xTyMatrix[0].size()-1]
		= xTx_xTyMatrix[xTx_xTyMatrix.size()-1][xTx_xTyMatrix[0].size()-1] * scalar;
    backSolve(xTx_xTyMatrix);

}

/**
 *	Eliminates a given row.
 *	@matrix the matrix the operation will effect
 *	@rowIt	the row the operation should occur on.
 */
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

/*
 *	@xTx_xTyMatrix take and xTx|xTy matrix and solves
 */
void solveMatrix(vector<vector<double> > &xTx_xTyMatrix)
{
	// Solve matrix
	for (int i = 0; i < xTx_xTyMatrix.size()-1; i++)
    {
		int lrgstRow = findLargestCol(xTx_xTyMatrix, i);
		// swap the rows.
        swapRow(xTx_xTyMatrix, i, lrgstRow);

		// scale the row.
        scale(xTx_xTyMatrix, i, xTx_xTyMatrix[i][i]);
        xTx_xTyMatrix[i][i] = 1;
        eliminate(xTx_xTyMatrix, i);
	}
    // Last row needs to be solved.
    solveLastRow(xTx_xTyMatrix);
}

