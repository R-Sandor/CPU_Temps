#include "interpolation.h"
#include "helper.h"
#include <iostream>
using namespace std;
using boost::multiprecision::cpp_dec_float_50;

/*
 * Assumption: the 2D vector (mathVect) is already the correct size.
 *
 *
 */
// vector< vector< vector<cpp_dec_float_50> > >
void createLi(liMatrix &mathVect, vector<double> &timeVect)
{


	// For each member of of timeVect create an Li index
	// containing a quotient and divisor.	
	for(int i = 0; i < timeVect.size(); i++) // Li
	{
		//vector<vector<cpp_dec_float_50> >
		liIndexVect liIndex(2);
		vector<cpp_dec_float_50> quotient (timeVect.size()-1);	
		vector<cpp_dec_float_50> divisor	(timeVect.size()-1);	
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
		// mathVect[0...N] would be each Li
		// Note this would need to be solved for the final
		// state of the quotient as at this time we do not 
		// know what our x value is yet.
		//
		// liIndex[1] is the divisor
		// The above funtion so should simply be running 
		// multiplication of the divisors.
		mathVect.push_back(liIndex);
		mathVect[i][0] = quotient;
		mathVect[i][1] = divisor;
	}
}

void solveLiDivisor(liMatrix &mathVect, vector<cpp_dec_float_50> &solvedDivs)
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

cpp_dec_float_50 solveLi(liMatrix &mathVect, vector< vector<double>> &data,
			   	int yCol, double x, vector<cpp_dec_float_50> &divisors, vector<cpp_dec_float_50>& quotients)
{

	cpp_dec_float_50 quotient = 0.0;
	cpp_dec_float_50 rTotal = 0.0;	// Running total
		
	// each li
	for (int i = 0; i < mathVect.size(); i++)
	{
		
	/*	if (quotients.size() == divisors.size()) 
		{
				rTotal += (quotients[i]/divisors[i])*data[yCol][i];
				continue;
		}
		// each vector qoutient/divisor
		for(int k = 0; k < mathVect[i][0].size(); k++)
		{
			if (k == 0)
			{
				quotient = x - mathVect[i][0][k];
				
			}
			else
			{
				quotient *= (x - mathVect[i][0][k]);
			if (quotient == 0)
				break;
			
			}
		}*/
		//quotients.push_back(quotient);
		rTotal += (quotients[i]/divisors[i])*data[yCol][i];
		
		quotient = 0.0;


	}
	return rTotal; 
}

cpp_dec_float_50 solveQuotients(liMatrix &mathVect, vector<cpp_dec_float_50>& quotients)
{

	cpp_dec_float_50 quotient = 0.0;
		
	// each li
	for (int i = 0; i < mathVect.size(); i++)
	{
		int x = 30*i;	
		// each vector qoutient/divisor
		for(int k = 0; k < mathVect[i][0].size(); k++)
		{
			if (k == 0)
			{
				quotient = x - mathVect[i][0][k];
				
			}
			else
			{
				quotient *= (x - mathVect[i][0][k]);
			if (quotient == 0)
				break;
			
			}
		}
		
		quotients.push_back(quotient);
	}
}
