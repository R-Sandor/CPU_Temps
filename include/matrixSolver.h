#ifndef MATRIX_SOLVER_H
#define MATRIX_SOLVER_H
#include <vector>
#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_dec_float_50;

using namespace std;
/*
 *	Multiplies one matrix by another matrix.
 *	Assumptions: 
 *	The second matrix's rows are equal to the first
 *	matrix's number of columns. Otherwise one can
 *	not do matrix multiplication.
 *
 *	Returns the resulting matrix.
 *
 *	@param lhs		left hand side
 *	@param rhs		right hand side
 *	@param result	resulting matrix
 */
void  multiplyer(std::vector< std::vector<double> >&lhs, 
				std::vector< std::vector<double>> &rhs,
				std::vector< std::vector<double>> &result);

/*
 * @param lhs       matrix
 * @param rhs       vector
 * @param result    resulting matrix
*/
void  multiplyVectByMat(std::vector< std::vector<double> >&lhs, 
				std::vector<double> &rhs,
				std::vector< std::vector<double>> &result);

/*
 * Returns the largest column's row, for example if we know that row 3 has a bigger
 * column 2 then we return the number 3. 
 * @param matrix		Ac|b matrix
 * @param iteration		iteration of finding the largest column
 */
int findLargestCol(std::vector<std::vector<double> > &matrix, int iteration);

/*
 * Swaps to matrix rows. 
 * @param matrix	Ac|b matrix
 * @param col		col that will have the row swap
 */ 
void swapRow(std::vector<std::vector<double> > &matrix, int col);

/*
 * scales the matrix by the largest column in the row. 
 *  @param matrix   input matrix
 *  @param loopIter the count of time scaling has previously happened
 *  @param scalar   the value that scales the matrix

 */
void scale(std::vector<std::vector<double> > &matrix, int loopIter, cpp_dec_float_50 scalar);


/*
 *	eliminates all of the other elements in that row, such that there
 *	will be only one element in that row that will be the value of that row.
 *	@param		xTx_xTyMatrix is the xTx_xTyMatri
 *	@loopIter	the Nth number of iterations.
 *
 */
void eliminate(std::vector<std::vector<double> > &matrix, int loopIter);


/*
 *	solves for the last row once all the other operations have completed
 *	@param xTx_xTyMatrix	Ac|b matrix
 */
void solveLastRow(vector<vector<double> > &xTx_xTyMatrix);


/**
 *	backsolve for each value of the identity matrix.
 *	@param matrix	Ac|b matrix
 *
 */
void backSolve(std::vector<std::vector<double> > &matrix);

/**
 *	solves for a matrix once the Ac|b matrix is established.
 *	@xTx_xTyMatrix	Ac|b matrix
 */
void solveMatrix(vector<vector<double> > &xTx_xTyMatrix);

/**
 *	@param takes vector as input to create the X matrix
 */
std::vector<std::vector<double> > createXMatrix(std::vector<double> &timeVect);

/**
 *	@param matrix takes a matrix and returns the transpose of matrix. 
 */
std::vector<std::vector<double> > createTMatrix(std::vector <std::vector<double> > &matrix);

#endif
