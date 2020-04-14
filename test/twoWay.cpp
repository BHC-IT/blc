#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "twoWay tested", "[twoWay]" ) {
	int port = blc::network::findFreePort();

	blc::network::server2way serv(5, port);
	blc::network::client2way client("localhost", port);
	blc::network::client2way clientEmpty;

	blc::tools::pipe masterPipe;
	blc::tools::pipe slavePipe(masterPipe.getSlave());

	serv.addPipe(masterPipe);
	serv.addFunc([&](const blc::network::Client &comm, const blc::network::Client &data, const blc::tools::pipe &pipe){
		comm << "ok\n";
		data << "test\n";

		pipe.waitWrite(10);
		pipe.write("start\n");

		pipe.waitRead(10);
		REQUIRE(pipe.read() == "ok");

		comm.waitRead(1000);
		data.waitRead(1000);
		REQUIRE(comm.read() == "ok");
		REQUIRE(data.read() == "test");

		comm << "ok\n";
		data << "test\n";

		pipe.waitRead(10);
		REQUIRE(pipe.read() == "ok");

		pipe.write("finish\n");
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
	});

	serv.getPipe() << "ok\n";

	REQUIRE(slavePipe.read() == "ok");
	slavePipe << "ok"; // setup branch for blc::network::server2way::parsePipe

	std::thread thr = serv.start();

	client.openComm();

	int rcvd = std::atoi(client.getComm().read().c_str());

	REQUIRE(rcvd != 0);

	client.setPortData(rcvd);

	client.openData();


	slavePipe.setBlock(true);

	std::string pipeName = slavePipe.read();
	int pipeId = std::stoi(pipeName);

	blc::tools::pipe reqSlave = serv.retrivePipe(pipeName);
	reqSlave.setBlock(true);

	REQUIRE(reqSlave.read() == "start");
	reqSlave << "ok\n";

	reqSlave = serv.retrivePipe(pipeId);
	reqSlave.setBlock(true);
	reqSlave << "ok\n";

	REQUIRE(serv.getOpenedClient() == 1);
	REQUIRE(serv.isIn(pipeId) == true);
	REQUIRE(serv.isIn(-1) == false);

	REQUIRE(client.readableComm() == true);
	REQUIRE(client.readableData() == true);
	REQUIRE(client.waitReadComm(10) == true);
	REQUIRE(client.waitReadData(10) == true);
	REQUIRE(client.getComm().read() == "ok");
	REQUIRE(client.getData().read() == "test");
	REQUIRE(client.readableComm() == false);
	REQUIRE(client.readableData() == false);


	REQUIRE(client.writableComm() == true);
	REQUIRE(client.writableData() == true);
	REQUIRE(client.waitWriteComm(10) == true);
	REQUIRE(client.waitWriteData(10) == true);
	client.write("ok\n");
	client.writeData("test\n");


	REQUIRE(client.read() == "ok");
	REQUIRE(client.readData() == "test");

	REQUIRE(client.getAddress() == "localhost");
	REQUIRE(client.getPort() == port);

	REQUIRE(client.getAddressData() == "localhost");
	REQUIRE(client.getPortData() == rcvd);

	REQUIRE(client.getBlock() == true);
	REQUIRE(client.getMode() == TCP);
	REQUIRE(client.getType() == AF_INET);

	REQUIRE(client.getBlockData() == true);
	REQUIRE(client.getModeData() == TCP);
	REQUIRE(client.getTypeData() == AF_INET);

	client.setAddress("localhost");
	client.setPort(port);
	client.setBlock(true);
	client.setMode(TCP);
	client.setType(AF_INET);

	client.setAddressData("localhost");
	client.setPortData(rcvd);
	client.setBlockData(true);
	client.setModeData(TCP);
	client.setTypeData(AF_INET);

	REQUIRE(serv.getMap().size() == serv.getChilds().size());


	REQUIRE(reqSlave.read() == "finish");
	client.close();

	slavePipe << "kill";

	serv.run(nullptr); // code coverage
	thr.join();
}
