#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "regex tested", "[regex]" ) {
	REQUIRE(blc::tools::regex("test", "test") == true);
	REQUIRE(blc::tools::regex("*", "test") == true);
	REQUIRE(blc::tools::regex("t*t", "test") == true);
	REQUIRE(blc::tools::regex("t*", "test") == true);
	REQUIRE(blc::tools::regex("*t", "test") == true);
	REQUIRE(blc::tools::regex("*", "") == true);

	REQUIRE(blc::tools::regex("tests", "test") == false);
	REQUIRE(blc::tools::regex("test", "tests") == false);
	REQUIRE(blc::tools::regex("z*t", "test") == false);
	REQUIRE(blc::tools::regex("t*s*t", "test") == false);
	REQUIRE(blc::tools::regex("", "test") == false);
	REQUIRE(blc::tools::regex("a", "") == false);
}
