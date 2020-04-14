#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "pipeCluster tested", "[pipeCluster]" ) {
	blc::tools::pipeCluster cluster;
	blc::tools::pipe masterPipe;
	blc::tools::pipe slavePipe(masterPipe.getSlave());

	blc::tools::pipe masterPipe2;
	blc::tools::pipe slavePipe2(masterPipe2.getSlave());

	cluster.pushBack(masterPipe);
	cluster.pushBack(slavePipe);
	masterPipe << "ok\n";
	REQUIRE(slavePipe.read() == "ok"); // setup

	masterPipe << "ok\n";
	REQUIRE(cluster[1].read() == "ok");

	masterPipe << "ok\n";
	REQUIRE(cluster.getCluster()[1].read() == "ok");

	cluster.setCluster({masterPipe, masterPipe2});

	cluster.writeToAll("ok\n");

	REQUIRE(slavePipe.read() == "ok");
	REQUIRE(slavePipe2.read() == "ok");

	masterPipe.close();
	cluster.writeToAll("ok\n");

	REQUIRE(slavePipe.read() == "");
	REQUIRE(slavePipe2.read() == "ok");

	masterPipe2.close();
}
