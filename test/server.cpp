#include "../blc/blc.hpp"
#include <iostream>
#include <unistd.h>

#include "catch.hpp"

class testServ : public blc::network::Server {
public:
	testServ(int port) : Server(2, port, true) {
	}

	void	run(void *userData) {
		struct sockaddr	client;
		while (this->_kill == false){
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
			if (this->_stop){
				REQUIRE(this->_wait ==  1000);
				this->_handle(0, client, 0);
			}
		}
	}
};

TEST_CASE( "server tested", "[server]" ) {
	int i = blc::network::findFreePort();
	testServ serv(i);

	std::thread th([&](){
		serv.run(nullptr);

		return (0);
	});

	REQUIRE(serv.getMaxClient() == 2);

	serv.setMaxClient(20);
	REQUIRE(serv.getMaxClient() == 20);
	REQUIRE(serv.getOpenedClient() == 0);

	REQUIRE(serv.getPort() == i);

	serv.handle([](int sock, struct sockaddr ad, int i){
		REQUIRE(sock == 0);
	});
	serv.wait(1000);
	serv.stop();

	serv.resume();

	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));

	serv.kill();
	th.join();
}
