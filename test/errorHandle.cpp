#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "errorHandle tests", "[errorHandle]" ) {
	try {
		throw blc::error::exception(traceError("nok"));
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("nok"));
		REQUIRE(e.where().find("errorHandle.cpp") != -1);
		REQUIRE(e.whom() == "void ____C_A_T_C_H____T_E_S_T____0()");
		REQUIRE(e.line() == 10);
		REQUIRE(e.when() == std::time(NULL));
	}

	REQUIRE(blc::tools::readable(std::cin) == false);
}
