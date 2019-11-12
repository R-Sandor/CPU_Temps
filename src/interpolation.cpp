#include "interpolation.h"
#include <iostream>
using namespace std;

/*
 * Assumption: the 2D vector (mathVect) is already the correct size.
 *
 *
 */
// vector< vector< vector<double> > >
void createLi(liMatrix &mathVect, vector<double> &timeVect)
{


	// For each member of of timeVect create an Li index
	// containing a quotient and divisor.	
	for(int i = 0; i < timeVect.size(); i++) // Li
	{
		//vector<vector<double> >
		liIndexVect liIndex(2);
		vector<double> quotient (timeVect.size()-1);	
		vector<double> divisor	(timeVect.size()-1);	
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
		// liIndex[0] is the quotient
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

double  solveLi(liMatrix &mathVect, vector< vector<double>>data, int yCol, double x)
{
	double result = 0;
	double quotient = 0.0;
	double divisor  = 0.0;
	double rTotal = 0.0;	// Running total
	// each li
	for (int i = 0; i < mathVect.size(); i++)
	{
		// each vector qoutient/divisor
		for (int j = 0; j < mathVect[i].size(); j++)
		{
			for(int k = 0; k < mathVect[i][j].size(); k++)
			{
				if (j == 0 && k == 0)
				{
					quotient = x - mathVect[i][j][k];
					continue;
				}
				else if (j == 1 && k == 0) 
				{
					divisor =  mathVect[i][j][k];
					continue;
				}
				if (j == 0)
					quotient *= (x - mathVect[i][j][k]);
				else
					divisor *= mathVect[i][j][k];
			}
		}
		
		rTotal += (quotient/divisor)*data[yCol][i];
		quotient = 0.0;
		divisor = 0.0;


	}
	return rTotal; 
}



