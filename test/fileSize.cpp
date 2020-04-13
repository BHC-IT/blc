#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "fileSize tested", "[fileSize]" ) {

	std::ifstream ifs("../test/filesize.test");
	std::filebuf fb;

	fb.open("../test/filesize.test", std::ios::in);
	std::istream is(&fb);

	REQUIRE(blc::tools::fileSize("../test/filesize.test") == 3);

	REQUIRE(blc::tools::fileSize(ifs) == 3);
	REQUIRE(blc::tools::fileSize(ifs, 1, std::ios_base::beg) == 3);
	REQUIRE(blc::tools::fileSize(ifs, 2, std::ios_base::beg) == 3);
	REQUIRE(blc::tools::fileSize(ifs, 2, std::ios_base::end) == 3);
	REQUIRE(blc::tools::fileSize(ifs, 2, std::ios_base::cur) == 3);

	ifs.close();
	REQUIRE(blc::tools::fileSize(ifs) == -1);
	REQUIRE(blc::tools::fileSize(ifs, 1, std::ios_base::beg) == -1);

	REQUIRE(blc::tools::fileSize(is) == 3);
	REQUIRE(blc::tools::fileSize(is, 1, std::ios_base::beg) == 3);
	REQUIRE(blc::tools::fileSize(is, 2, std::ios_base::beg) == 3);
	REQUIRE(blc::tools::fileSize(is, 2, std::ios_base::end) == 3);
	REQUIRE(blc::tools::fileSize(is, 2, std::ios_base::cur) == 3);
}
