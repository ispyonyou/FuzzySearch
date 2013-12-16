#include "FuzzySearch.h"
#include <iostream>

int main( int argc, char* argv[] )
{
  {
	  std::vector< unsigned int > maxWeightSequence;
	  bool isMatch = FuzzySearch().IsMatch( "Asd Dsa asd", "", maxWeightSequence );

		_ASSERT( isMatch == true );
	}

	{
    std::vector< unsigned int > maxWeightSequence;
	  bool isMatch = FuzzySearch().IsMatch( "Asd Dsa asd", " \\ \\", maxWeightSequence );

		_ASSERT( isMatch == true );
	}

	{
    std::vector< unsigned int > maxWeightSequence;
	  bool isMatch = FuzzySearch().IsMatch( "Asd Dsa asd", "adsk", maxWeightSequence );

		_ASSERT( isMatch == false );
	}

	{
    std::vector< unsigned int > maxWeightSequence1;
		bool isMatch1 = FuzzySearch().IsMatch( "Asd Dsa asd", "ads", maxWeightSequence1 );

    std::vector< unsigned int > maxWeightSequence2;
		bool isMatch2 = FuzzySearch().IsMatch( "Asd Dsa asd", "a ds", maxWeightSequence2 );

    std::vector< unsigned int > maxWeightSequence3;
		bool isMatch3 = FuzzySearch().IsMatch( "Asd Dsa asd", " ad\\s", maxWeightSequence3 );

    std::vector< unsigned int > maxWeightSequence4;
		bool isMatch4 = FuzzySearch().IsMatch( "Asd Dsa asd", "ads\\", maxWeightSequence4 );

		_ASSERT( ( isMatch1 == isMatch2 ) && ( isMatch2 == isMatch3 ) && 
             ( isMatch3 == isMatch4 ) && ( isMatch4 == true ) &&
			       ( maxWeightSequence1 == maxWeightSequence2 ) && ( maxWeightSequence2 == maxWeightSequence3 ) && 
             ( maxWeightSequence3 == maxWeightSequence4 ) );

    for each( unsigned int index in maxWeightSequence1 )
      std::cout << index << " ";
    std::cout << std::endl;
	}

	std::cout << "all test executed" << std::endl 
		      << "press (eneter) to exit" << std::endl;

	getchar();
	return 0;
}