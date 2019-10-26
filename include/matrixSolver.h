#ifndef MATRIX_SOLVER_H
#define MATRIX_SOLVER_H
#include <vector>


/*
 *	Multiplies one matrix by another matrix.
 *	Assumptions: 
 *	The second matrix's rows are equal to the first
 *	matrix's number of columns. Otherwise one can
 *	not do matrix multiplication.
 *
 *	Returns the resulting matrix.
 */
std::vector<std::vector<double>>  multiplyer(std::vector< std::vector<double> >lhs, 
				std::vector< std::vector<double>> rhs);


/*
 * Returns the largest column's row, for example if we know that row 3 has a bigger
 * column 2 then we return the number 3. 
 */
int findLargestCol(std::vector<std::vector<double> > &matrix, int iteration);

/*
 * Swaps to matrix rows. 
 */ 
void swapRow(std::vector<std::vector<double> > &matrix, int col);

/*
 * scales the matrix by the largest column in the row. 
 */
void scale(std::vector<std::vector<double> > &matrix, int loopIter, double scalar);


/*
 *	eliminates all of the other elements in that row, such that there
 *	will be only one element in that row that will be the value of that row.
 *
 */
void eliminate(std::vector<std::vector<double> > &matrix, int loopIter);


void backSolve(std::vector<std::vector<double> > &matrix);

#endif
