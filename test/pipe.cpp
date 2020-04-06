#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "Pipe tested", "[pipe]" ) {
	blc::tools::pipe pipe;

	blc::tools::pipe masterPipe = pipe.getMaster();
	blc::tools::pipe slavePipe = pipe.getSlave();

	REQUIRE(slavePipe.getState() == false);
	REQUIRE(masterPipe.getState() == true);

	masterPipe << "test\n";
	REQUIRE(slavePipe.read() == "test");
	REQUIRE(slavePipe.read() == "" );

	masterPipe << "test";
	REQUIRE(slavePipe.read() == "test");
	REQUIRE(slavePipe.read() == "");

	masterPipe.close();

	REQUIRE(masterPipe.isClosed() == true);
	REQUIRE(slavePipe.isClosed() == true);

	REQUIRE(masterPipe.readable() == false);
	REQUIRE(slavePipe.readable() == false);

	REQUIRE(masterPipe.writable() == false);
	REQUIRE(slavePipe.writable() == false);

	masterPipe << "test";
	REQUIRE(slavePipe.read() == "");
}
