#include "../blc/blc.hpp"
#include <iostream>
#include <unistd.h>

#include "catch.hpp"

class testServActor : public blc::network::Server, public blc::tools::actor<testServActor> {
public:
	testServActor(int port) : Server(2, port, true) {
		this->start();
	}

	void	run(void *userData) {
		while (this->_kill == false){
			struct sockaddr	client;
			int sock = this->accept(&client);
			if (sock > 0){

				blc::network::Client cl(sock, client);

				cl << "ok\n"; // 1

				REQUIRE(cl.read() == "ok"); //  2

				cl << "ok\n";  // 3


				usleep(5000);
				std::string tmp;

				cl >> tmp;
				REQUIRE(tmp == "test"); // 4

				std::cout << cl << std::endl; // 5

				usleep(50);
				cl << "ok\n"; // 6

				cl.read(); //  7, after close

				usleep(5000);
				REQUIRE(cl.readable() == false);
				this->kill();
			}
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
		}
	}

	void	lifeCycle() {
		this->run(nullptr);
	}
};

TEST_CASE( "socket tested", "[socket]" ) {
	int i = blc::network::findFreePort();

	blc::network::Socket testable;

	try {
		testable.open();
	} catch (blc::error::exception &e){
		REQUIRE(e.what() == std::string("Error : non set connection"));
	}

	testable.setAddress("localhost");
	testable.setPort(i);
	testable.setType(0);

	REQUIRE(testable.getAddress() ==  "localhost");
	REQUIRE(testable.getPort() ==  i);
	REQUIRE(testable.getBlock() ==  false);
	REQUIRE(testable.getType() ==  0);


	testServActor serv(i);

	usleep(5000);
	blc::network::Socket sock("127.0.0.1", i);
	sock.open();

	sock.setBlock(false);
	REQUIRE(sock.getBlock() ==  false);

	sock.setBlock(true);
	REQUIRE(sock.getBlock() ==  true);

	sock.setMode(TCP);
	REQUIRE(sock.getMode() == TCP);


	REQUIRE(sock.read() == "ok"); // 1
	REQUIRE(sock.readable() == false);
	sock << "ok\n"; // 2

	usleep(5000);
	REQUIRE(sock.readable() == true);
	REQUIRE(sock.writable() == true);
	REQUIRE(sock.isOpen() == true);
	REQUIRE(sock.isClosed() == false);
	REQUIRE(sock.read(3) == "ok\n"); // 3

	REQUIRE(sock.waitWrite(5) == true);
	sock << "test\n"; // 4
	sock << "test\n"; // 5

	sock.setBlock(false);
	REQUIRE(sock.waitRead(5) == false);
	REQUIRE(sock.waitRead(100000) == true);
	REQUIRE(sock.read() == "ok"); // 6

	sock.close();
	REQUIRE(sock.isOpen() == false);
	REQUIRE(sock.isClosed() == true);
	REQUIRE(sock.writable() == false);
	try {
		sock << "test\n"; // 7, bad
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : not opened"));
	}
	try {
		sock.read();
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : not opened"));
	}

	try {
		sock.read(5);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : not opened"));
	}

	blc::network::Socket failer("age", 5000);
	try {
		failer.open();
	} catch (blc::error::exception &e) {
	}

	blc::network::Socket google("google.com", 80);
	try {
		failer.open();
	} catch (blc::error::exception &e) {
	}

	blc::network::Socket sock2("127.0.0.1", i);
	sock2.open();
	sock2.open();

	usleep(5000);
}
