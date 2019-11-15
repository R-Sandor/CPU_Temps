#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <boost/multiprecision/cpp_dec_float.hpp> // very large numbers happen 
												  // in lagrange interpolation
using namespace std;
using boost::multiprecision::cpp_dec_float_50;

// li 0...N
typedef  vector<vector<cpp_dec_float_50> >  liIndexVect;
// contains all of LiIndexs 0..N
typedef vector<liIndexVect> liMatrix;


/*
 *	Sets up all Li indexs
 *
 *	@param mathVect the mathVect is simply 2D vector
 *	the first index containing the qoutient, the second 
 *	containing the divisor. 
 *
 *	@param timeVect can be thought of as the x vector, 
 *	contains 0-N seconds for which the reading were taken from the CPUs.
 */
void createLi(liMatrix &mathVect, vector<double> &timeVect);

/*
*	@param mathVect after each index of li is establish with x-xk/xi-xk
*	the x needs to have a value before it can be solved. This function takes
*	and places in the formula and solves by multiplying out the interpolation 
*	formula
*	@param x a given x value.
*
*
*/
void solveLiDivisor(liMatrix &mathVect, vector<cpp_dec_float_50> &solvedDivs);

cpp_dec_float_50 solveLi(liMatrix &mathVect, vector< vector<double>> &data,
				int yCol, double x, vector<cpp_dec_float_50> &divisors, vector<cpp_dec_float_50>& quotients);

cpp_dec_float_50 solveQuotients(liMatrix &mathVect, vector<cpp_dec_float_50>& quotients);




#endif
