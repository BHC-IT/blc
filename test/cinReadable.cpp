#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "cinReadable tests", "[cinReadable]" ) {
	REQUIRE(blc::tools::cinReadable() == false);

	REQUIRE(blc::tools::readable(std::cin) == false);
}
