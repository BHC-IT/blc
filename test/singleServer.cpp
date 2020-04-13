#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "singleServer tested", "[singleServer]" ) {
	int port = blc::network::findFreePort();
	blc::network::singleServer serv(port);

	try {
		serv.run();
	} catch (blc::error::exception &e){
		REQUIRE(e.what() == std::string("Error : handle function not specified"));
	}

	serv.handle([&](const blc::network::Client &client){
		client.waitRead(10);

		REQUIRE(client.read() == "ok");

		client << "ok\n";
	});

	std::thread thr([&](){
		serv.run();
	});

	blc::network::Socket sock("localhost", port);

	sock.open();
	sock << "ok\n";
	REQUIRE(sock.read() == "ok");

	sock.close();
	serv.kill();
	sock.open();
	sock << "ok\n";
	REQUIRE(sock.read() == "ok");
	sock.close();

	thr.join();
	serv.run(nullptr); // code coverage
}
