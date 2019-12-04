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


/*
 * I have solved out the Lagrange interpolation in away that took advantage of what
 * I know about interpolation. There will only ever be one value that is significant 
 * when all of the various lis have been totaled. I know that each of my functions relate
 * to a single time as well. So as the loop increase for each point I solve lagrange interpolation 
 * for that point. 
 * @param mathVect the vector that contains all of elements of Li
 * e.g. mathVect[0][#][#] - is the first li (l0)
 *      mathVect[0][0][#] - is l0s quotients vector
 *      mathVect[0][1][#] - is the precomputed divisors of l0
 *      mathVect[0][0][0] - is the first quotient of N-1 quotients 
 *  
 * @param quotients is an empty vector that is passed in to be solved.
 *
 */
void solveQuotients(liMatrix &mathVect, vector<cpp_dec_float_50>& quotients);


/**
 *	prints to file the least squares of a given point
 *	prints to file the interpolation of a point.
 *
 *	@param c0			the constant c0 value of least squares
 *	@param c1			the xC1 value of least squares as a part of phi hat
 *	@param quotients	each quotient as a result of Lagrange interpolation
 *	@param divisors		each divisor as a result of lagrange interpolation
 *	@param linearData	the linear interpolation points
 *	@param data			the y data points
 *	@param outputFile	the output file
 *	@param datCol		the core that is being approximated
 *	@param numOfWrite	the number lines output
 */
void printFile(double c0, 
                double c1, 
                vector<cpp_dec_float_50> &quotients,
                vector<cpp_dec_float_50> &divisors, 
                vector< vector<double> > &data, 
				vector<double> &linearData,
                ofstream &outputFile, 
                int dataCol,
                int numOfWrites);

/**  
 * @param xData         the X points
 * @param yData         the Y points
 * @param x             the input point.
 */   
double interpolate(vector<double> &xData, vector<double> &yData, double x);

#endif
