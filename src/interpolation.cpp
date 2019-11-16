#include "interpolation.h"
#include "helper.h"
#include <iostream>
#include <fstream> //File reader(ifstream)
using namespace std;
using boost::multiprecision::cpp_dec_float_50;

/*
 *	What this function does is it sets up the problem to be broken down further
 *	by establishing all of the products of the quotient & divisors.
 *
 *	It skips problems that will provide a 0 in the divisor or the index.
 *	what this does is leaves only the significant value of the quotient in the quotient
 *	part of the mathVect.
 *
 *	Which means when the product is solved for any given Li, the Lagrange value can
 *	be determined by taking the quotient[i]/divisor[i]*y[i] and get the correct value.
 *
 * Assumption: the 2D vector (mathVect) is already the correct size.
 * @param mathVect liMatrix is a typedef defined in interpolation.h.
 *		typedef  vector<vector<cpp_dec_float_50> >  liIndexVect;
 *		typedef vector<liIndexVect> liMatrix;
 * @timeVect vector	containing all of the x points (cpu temp readings).
 */
void createLi(liMatrix &mathVect, vector<double> &timeVect)
{


	// For each member of of timeVect create an Li index
	// containing a quotient and divisor.	
	for(int i = 0; i < timeVect.size(); i++) // Li
	{
		//vector<vector<cpp_dec_float_50> >
		liIndexVect liIndex(2);
		vector<cpp_dec_float_50> quotient(timeVect.size()-1);	
		vector<cpp_dec_float_50> divisor(timeVect.size()-1);	

		// loop through all of the possible functions
		int k = 0;
		for(int j = 0; j < timeVect.size(); j++)
		{
			if (j == i)
			{	
				continue;
			}

			quotient[k]	 = timeVect[j];
			divisor[k]	= timeVect[i] - timeVect[j];
			k++;
		}
		mathVect.push_back(liIndex);
		mathVect[i][0] = quotient;
		mathVect[i][1] = divisor;
	}
}

/*
 * @param mathVect the vector that contains all of elements of Li
 * e.g. mathVect[0][#][#] - is the first li (l0)
 *		mathVect[0][0][#] - is l0s quotients vector
 *		mathVect[0][1][#] - is the precomputed divisors of l0
 *		mathVect[0][0][0] - is the first quotient of N-1 quotients 
 *	
 * @param solvedDivs is an empty vector that is passed in to be solved.
 */
void solveLiDivisor(liMatrix &mathVect, 
				vector<cpp_dec_float_50> &solvedDivs)
{
	cpp_dec_float_50 divisor  = 0.0;
	// each li
	for (int i = 0; i < mathVect.size(); i++)
	{
		// each vector qoutient/divisor
		// j = 0 - qoutient 
		// j = 1 - divisor
		for(int k = 0; k < mathVect[i][1].size(); k++)
		{
			if (k == 0) 
			{
				divisor =  mathVect[i][1][k];
				continue;
			}
			else	divisor *= mathVect[i][1][k];
			
		}
		
		solvedDivs.push_back(divisor);
		divisor = 0.0;
		
	}
}

/*
 * I have solved out the Lagrange interpolation in away that took advantage of what
 * I know about interpolation. There will only ever be one value that is significant 
 * when all of the various lis have been totaled. I know that each of my functions relate
 * to a single time as well. So as the loop increase for each point I solve lagrange interpolation 
 * for that point. 
 * @param mathVect the vector that contains all of elements of Li
 * e.g. mathVect[0][#][#] - is the first li (l0)
 *		mathVect[0][0][#] - is l0s quotients vector
 *		mathVect[0][1][#] - is the precomputed divisors of l0
 *		mathVect[0][0][0] - is the first quotient of N-1 quotients 
 *	
 * @param quotients is an empty vector that is passed in to be solved.
 *
 */
void solveQuotients(liMatrix &mathVect, vector<cpp_dec_float_50>& quotients)
{
	cpp_dec_float_50 quotient = 0.0;
	// each li
	for (int i = 0; i < mathVect.size(); i++)
	{
		// We only need to solve for the quotient of time readings i.e.,
		// 0, 30, 60, 90 secs ... to i*30 seconds	
		int x = 30*i;	
		// each vector qoutient/divisor
		for(int k = 0; k < mathVect[i][0].size(); k++)
		{
			if (k == 0)
			{
				quotient = x - mathVect[i][0][k];
			}
			else
				quotient *= (x - mathVect[i][0][k]);
			
		}
		quotients.push_back(quotient);
	}
}

/**
 *
 * @param c0	constant value in phi hat  
 * @param c1	xc1 value.
 * @quotients	the significant value li
 * @divisors	the multiplied out divisors
 * @data		the original y value points
 * @outFile		ofstream to output data
 * @dataCol		the core that the data is related to
 * @numWrite	the count of data lines read.
 */
void printFile(double c0, 
				double c1, 
				vector<cpp_dec_float_50> &quotients, 
				vector<cpp_dec_float_50> &divisors, 
				vector< vector<double> > &data, 
				ofstream &outputFile, 
				int dataCol,
				int numOfWrites)
{
	for (int write_index = 0; write_index < numOfWrites; write_index++)
	{
		outputFile << "0 <= " <<  write_index * 30 <<  "< " << numOfWrites*30 <<  "; " << "y" << write_index << "= "
				   << c0 + c1*30*write_index << "; Least Squares";
        outputFile << endl;
 
        outputFile << "0 <= " <<  write_index * 30 <<  "< " << numOfWrites*30 <<  "; " << "y" << write_index << "= "
                   << quotients[write_index]/divisors[write_index]*data[dataCol][write_index] << "; lagrange interpolation";
        outputFile << endl;
    }
    outputFile.close();
}


