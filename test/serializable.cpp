#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "serializable tested", "[serializable]" ) {
	std::string tmp = blc::tools::serializable::stringToHex("abcdefghijklmnopqrstuvwxyz 0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	REQUIRE("abcdefghijklmnopqrstuvwxyz 0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ" == blc::tools::serializable::hexToString(tmp));
}
