#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "float tested", "[float]" ) {
	blc::math::Float f;
	blc::math::Float f2(1.5);
	blc::math::Float f3(1.5, 1);
	blc::math::Float f4(f);

	//trash construct
	REQUIRE(blc::math::Float(0) == 0);
	REQUIRE(blc::math::Float(1500) == 1500);
	REQUIRE(blc::math::Float(-1500) == -1500);
	REQUIRE(blc::math::Float(0.05) == 0.05);
	REQUIRE(blc::math::Float(-0.05) == -0.05);
	REQUIRE(blc::math::Float(0, 0) == 0);

	REQUIRE((f = 0) == 0);
	REQUIRE((f = 1500) == 1500);
	REQUIRE((f = -1500) == -1500);
	REQUIRE((f = 0.05) == 0.05);
	REQUIRE((f = -0.05) == -0.05);

	f = 0;
	f4 = f2;

	REQUIRE(f2 == 1.5);
	REQUIRE(f3 == 15);

	REQUIRE(f2 + 1.5 == 3);
	REQUIRE(f2 - 2 == -0.5);
	REQUIRE(f2 * 2 == 3);
	REQUIRE(f2 / 1.5 == 1);

	REQUIRE(f2 + 0.5 == 2);
	REQUIRE(f2 - 0.5 == 1);
	REQUIRE(f2 * 0.5 == 0.75);
	REQUIRE(f2 / 0.1 == 15);

	REQUIRE(f2 + f3 == 16.5);
	REQUIRE(f2 - f3 == -13.5);
	REQUIRE(f2 * f3 == 22.5);
	REQUIRE(f2 / f3 == 0.1);

	REQUIRE((f2 >= 0.1) == true);
	REQUIRE((f2 > 0.1) == true);
	REQUIRE((f2 < 0.1) == false);
	REQUIRE((f2 <= 0.1) == false);

	REQUIRE((f2 >= 10) == false);
	REQUIRE((f2 > 10) == false);
	REQUIRE((f2 < 10) == true);
	REQUIRE((f2 <= 10) == true);

	REQUIRE((f2 >= 1.5) == true);
	REQUIRE((f2 > 1.5) == false);
	REQUIRE((f2 <= 1.5) == true);
	REQUIRE((f2 < 1.5) == false);

	REQUIRE((f2 >= f3) == false);
	REQUIRE((f2 > f3) == false);
	REQUIRE((f2 <= f3) == true);
	REQUIRE((f2 < f3) == true);

	REQUIRE((f3 >= f2) == true);
	REQUIRE((f3 > f2) == true);
	REQUIRE((f3 <= f2) == false);
	REQUIRE((f3 < f2) == false);

	REQUIRE((f2 == 0) == false);
	REQUIRE((f2 == 1.5) == true);
	REQUIRE((f2 == f3) == false);
	REQUIRE((f2 == f) == false);
	REQUIRE((f2 == f4) == true);

	REQUIRE((f2 != 0) == true);
	REQUIRE((f2 != 1.5) == false);
	REQUIRE((f2 != f3) == true);
	REQUIRE((f2 != f) == true);
	REQUIRE((f2 != f4) == false);

	REQUIRE((f2 > f4) == false);
	REQUIRE((f2 >= f4) == true);
	REQUIRE((f2 < f4) == false);
	REQUIRE((f2 <= f4) == true);

	f2 = 50000000000;

	REQUIRE(f2 == 50000000000);
	REQUIRE(f2() == 50000000000);
	REQUIRE(f2.calculate() == 50000000000);

	f2.align();

	REQUIRE(f2 == 50000000000);
	REQUIRE(f2() == 50000000000);
	REQUIRE(f2.calculate() == 50000000000);

	f3 = f2;

	REQUIRE(f3 == 50000000000);
	REQUIRE(f3 == f2);


	f = 0.0;

	f.setNb(100000);

	REQUIRE(f == 100000);
	f.align(1);
	REQUIRE(f == 100000);
	REQUIRE(f.getNb() == 1000000);
	REQUIRE(f.getE() == -1);

	f.align();
	REQUIRE(f == 100000);
	REQUIRE(f.getNb() == 1);
	REQUIRE(f.getE() == 5);

	f.align(-5);
	REQUIRE(f == 100000);
	REQUIRE(f.getNb() == 0.00001);
	REQUIRE(f.getE() == 10);

	f.align();
	REQUIRE(f == 100000);
	REQUIRE(f.getNb() == 1);
	REQUIRE(f.getE() == 5);

	REQUIRE(f.serialize() == ""); //TODO
	f.unserialize("");  // TODO

}
