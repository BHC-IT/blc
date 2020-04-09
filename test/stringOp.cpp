#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "stringOp tested", "[stringOp]" ) {
	std::string tmp = "1234";
	std::string tmp2 = "A1234";

	REQUIRE(blc::tools::isNumber("") == false);
	REQUIRE(blc::tools::isNumber(tmp) == true);
	REQUIRE(blc::tools::isNumber(tmp2) == false);

	std::vector<std::string> res;

	res = blc::tools::cut(tmp, '2');
	REQUIRE(res[0] == "1");

	res = blc::tools::cut(tmp, "3");
	REQUIRE(res[0] == "12");
}
