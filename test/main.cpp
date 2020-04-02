#include "../blc/blc.hpp"
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
	return number <= 1 ? number : Factorial(number-1)*number;
}


TEST_CASE( "Factorials are computed", "[factorial]" ) {
	REQUIRE( Factorial(3) == 6 );
}
