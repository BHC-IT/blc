#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "Pipe tested", "[pipe]" ) {
	blc::tools::pipe pipe;

	blc::tools::pipe masterPipe = pipe.getMaster();
	blc::tools::pipe slavePipe = pipe.getSlave();

	blc::tools::pipe test(true, true);

	REQUIRE(test.getState() == true);
	REQUIRE(test.getBlock() == true);
	REQUIRE(test.isClosed() == false);

	blc::tools::pipe slavePipe2(slavePipe);
	blc::tools::pipe slavePipe3(slavePipe, false, false);

	REQUIRE(slavePipe.getState() == false);
	REQUIRE(masterPipe.getState() == true);

	masterPipe << "test\n";
	REQUIRE(slavePipe.readable() == true);
	REQUIRE(slavePipe.read() == "test");
	REQUIRE(slavePipe.read() == "" );

	slavePipe3.setBlock(false);

	slavePipe3.switchState();
	slavePipe3.switchState();

	masterPipe << "test\n";
	REQUIRE(slavePipe3.read() == "test");
	REQUIRE(slavePipe3.read() == "" );


	test = slavePipe3;
	masterPipe << "test\n";
	REQUIRE(test.read() == "test");
	REQUIRE(test.read() == "" );


	slavePipe3.setBlock(false);

	REQUIRE(masterPipe.readable() == false);
	REQUIRE(masterPipe.writable() == true);

	REQUIRE(slavePipe.readable() == false);
	REQUIRE(slavePipe.writable() == true);

	slavePipe3 << "test\n";
	REQUIRE(masterPipe.readable() == true);
	REQUIRE(masterPipe.read(5) == "test");
	REQUIRE(masterPipe.read() == "" );

	masterPipe << "test";
	REQUIRE(slavePipe.read() == "test");
	REQUIRE(slavePipe.read() == "");

	slavePipe3.setBlock(true);
	masterPipe.setBlock(true);

	masterPipe << "test";

	REQUIRE(slavePipe3.read(5) == "test");

	slavePipe3.setBlock(true);
	masterPipe.setBlock(true);


	masterPipe << "test";

	std::string tmp;
	slavePipe >> tmp;
	REQUIRE(tmp == "test");

	masterPipe.close();

	REQUIRE(masterPipe.isClosed() == true);
	REQUIRE(slavePipe.isClosed() == true);

	REQUIRE(masterPipe.readable() == false);
	REQUIRE(slavePipe.readable() == false);

	REQUIRE(masterPipe.writable() == false);
	REQUIRE(slavePipe.writable() == false);

	masterPipe.waitRead(1);
	masterPipe.waitWrite(1);

	masterPipe << "test";
	REQUIRE(slavePipe.read() == "");
}
