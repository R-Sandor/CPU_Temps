#include "interpolation.h"

using namespace std;

/*
 * Assumption: the 2D vector (mathVect) is already the correct size.
 *
 *
 */

void createLi(liMatrix &mathVect, vector<double> &timeVect)
{
	// used to keep track of the xK index
	int xk = 0;
	// For each member of of timeVect create an Li index
	// containing a qoutient and divisor.	
	for(int i = 0; i < timeVect.size(); i++)
	{
		liIndexVect idV;
		vector<double> qoutient (timeVect.size());	
		vector<double> divisor (timeVect.size());	

		// loop through all of the possible functions
		for(int j = 0; j < timeVect.size(); j++)
		{
			if (j == xk)
			{	
				xk++;
				continue;
			}

			qoutient[i]	= timeVect[i] - timeVect[j];
			divisor[i]	= -timeVect[j];

			xk++;
		}
		xk =0;	
		mathVect[0].push_back(qoutient);
		mathVect[1].push_back(divisor);
	}
}

void solveLi(liMatrix mathVect, double x)
{

}


