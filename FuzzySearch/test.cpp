#include "FuzzySearch.h"
#include <iostream>

int main( int argc, char* argv[] )
{
    {
	    long weight = 0;
	    bool isMatch = FuzzySearch::IsMatch( "Asd Dsa asd", "", weight );

		_ASSERT( isMatch == true && weight == 0 );
	}

	{
	    long weight = 0;
	    bool isMatch = FuzzySearch::IsMatch( "Asd Dsa asd", " \\ \\", weight );

		_ASSERT( isMatch == true && weight == 0 );
	}

	{
	    long weight = 0;
	    bool isMatch = FuzzySearch::IsMatch( "Asd Dsa asd", "adsk", weight );

		_ASSERT( isMatch == false && weight == 0 );
	}

	{
		long weight1 = 0;
		bool isMatch1 = FuzzySearch::IsMatch( "Asd Dsa asd", "ads", weight1 );

		long weight2 = 0;
		bool isMatch2 = FuzzySearch::IsMatch( "Asd Dsa asd", "a ds", weight2 );

		long weight3 = 0;
		bool isMatch3 = FuzzySearch::IsMatch( "Asd Dsa asd", " ad\\s", weight3 );

		long weight4 = 0;
		bool isMatch4 = FuzzySearch::IsMatch( "Asd Dsa asd", "ads\\", weight4 );

		_ASSERT( ( isMatch1 == isMatch2 ) && ( isMatch2 == isMatch3 ) && ( isMatch3 == isMatch4 ) && ( isMatch4 == true ) &&
			     ( weight1 == weight2 ) && ( weight2 == weight3 ) && ( weight3 == weight4 ) && ( weight4 == 6 ) );
	}

	std::cout << "all test executed" << std::endl 
		      << "press (eneter) to exit" << std::endl;

	getchar();
	return 0;
}