#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "matrixSolver.h"
unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}


TEST_CASE("Matrix Multiplication", "[matrix_mult]")
{
	vector< vector<double> > lhs {{1, 2, 3},
								  {4, 5, 6},
								  {7, 8, 9}};
	vector< vector<double> > rhs { {1},
								   {2},
							       {3}};	   
	vector< vector<double> > result;
	multiplyer(lhs, rhs, result);
	vector <vector<double> > correct {	{14},
										{32},
										{50}};
	REQUIRE( correct == result);
					
	
}
