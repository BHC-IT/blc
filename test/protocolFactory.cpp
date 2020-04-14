#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "Factory tested", "[factory]" ) {
	blc::tools::protocolCaps<int, int> caps;

	caps.setCode(200);

	REQUIRE(caps.getCode() == 200);

	REQUIRE(caps.check(200) == true);
	REQUIRE(caps.check(201) == false);

	caps.setCallback([=](int val){
		REQUIRE(val == 5);
		return (2);
	});

	REQUIRE(caps.activate(5) == 2);
	caps << 5;

	caps = 201;

	REQUIRE(caps.getCode() == 201);

	REQUIRE(caps.check(200) == false);
	REQUIRE(caps.check(201) == true);

	caps = [=](int val){
		REQUIRE(val == 5);
		return(3);
	};

	REQUIRE(caps.checkAndActive(201, 5) == 3);

	blc::tools::protocolCaps<int, int> secCaps;

	secCaps = caps;

	REQUIRE(secCaps.checkAndActive(201, 5) == 3);

	blc::tools::protocolCaps<int, int> thirdCaps(caps);

	REQUIRE(thirdCaps.checkAndActive(201, 5) == 3);

	blc::tools::protocolCaps<int, int> fourthCaps(std::move(caps));

	REQUIRE(fourthCaps.checkAndActive(201, 5) == 3);
	REQUIRE(caps.getCode() == 0);
}
