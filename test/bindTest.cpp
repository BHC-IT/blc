#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "bindTest tested", "[bindTest]" ) {

	int i = blc::network::findFreePort();
	REQUIRE(blc::network::isPortFree(i) == true);
}
